
#include <algorithm>
#include "../common/CLog.h"
#include "../game/chars/CChar.h"
#include "../game/items/CItemShip.h"
#include "../game/CWorld.h"
#include "../game/CWorldGameTime.h"
#include "../sphere/ProfileTask.h"
#include "CException.h"
#include "CRect.h"
#include "CSectorTemplate.h"


////////////////////////////////////////////////////////////////////////
// -CCharsDisconnectList

void CCharsDisconnectList::AddCharDisconnected( CChar * pChar )
{
    ADDTOCALLSTACK("CCharsDisconnectList::AddCharDisconnected");
    pChar->SetUIDContainerFlags(UID_O_DISCONNECT);
    CSObjCont::InsertContentTail(pChar);
}

////////////////////////////////////////////////////////////////////////
// -CCharsActiveList

CCharsActiveList::CCharsActiveList()
{
	m_iTimeLastClient = 0;
	m_iClients = 0;
}

void CCharsActiveList::OnRemoveObj(CSObjContRec* pObjRec )
{
	ADDTOCALLSTACK("CCharsActiveList::OnRemoveObj");
    ASSERT(pObjRec);

	// Override this = called when removed from group.
	CChar * pChar = static_cast<CChar*>(pObjRec);
	if (pChar->IsClient())
	{
		--m_iClients;
        m_iTimeLastClient = CWorldGameTime::GetCurrentTime().GetTimeRaw();	// mark time in case it's the last client
	}

	CSObjCont::OnRemoveObj(pObjRec);
	pChar->SetUIDContainerFlags(UID_O_DISCONNECT);
}

void CCharsActiveList::AddCharActive( CChar * pChar )
{
	ADDTOCALLSTACK("CCharsActiveList::AddCharActive");
	ASSERT( pChar );
	// ASSERT( pChar->m_pt.IsValid());
	CSObjCont::InsertContentTail(pChar); // this also removes the Char from the old sector
    // UID_O_DISCONNECT is removed also by SetTopPoint. But the calls are in this order: SetTopPoint, then AddCharActive -> CSObjList::InsertContentHead(pChar) ->-> OnRemoveObj
    //  (which sets UID_O_DISCONNECT), then we return in AddCharActive, where we need to manually remove this flag, otherwise we need to call SetTopPoint() here.
    pChar->RemoveUIDFlags(UID_O_DISCONNECT);
    if (pChar->IsClient())
    {
		++m_iClients;
    }
}

//////////////////////////////////////////////////////////////
// -CItemList

bool CItemsList::sm_fNotAMove = false;

void CItemsList::OnRemoveObj(CSObjContRec* pObRec)
{
	ADDTOCALLSTACK("CItemsList::OnRemoveObj");

	// Item is picked up off the ground. (may be put right back down though)
	CItem * pItem = static_cast<CItem*>(pObRec);

	if ( ! sm_fNotAMove )
	{
		pItem->OnMoveFrom();	// IT_MULTI, IT_SHIP and IT_COMM_CRYSTAL
	}

	CSObjCont::OnRemoveObj(pObRec);
	pItem->SetUIDContainerFlags(UID_O_DISCONNECT);	// It is no place for the moment.
}

void CItemsList::AddItemToSector( CItem * pItem )
{
	ADDTOCALLSTACK("CItemsList::AddItemToSector");
	// Add to top level.
	// Either MoveTo() or SetTimeout is being called.
	ASSERT( pItem );
	CSObjCont::InsertContentTail( pItem ); // this also removes the Char from the old sector
    pItem->RemoveUIDFlags(UID_O_DISCONNECT);
}


//////////////////////////////////////////////////////////////////
// -CSectorBase::CObjPointSortArray


int CSectorBase::CObjPointSortArray::CompareKey( int id, CPointSort* pBase, bool fNoSpaces ) const
{
    UNREFERENCED_PARAMETER(fNoSpaces);
    ASSERT( pBase );
    return (id - pBase->GetPointSortIndex());
}


//////////////////////////////////////////////////////////////////
// -CSectorBase

void CSectorBase::SetAdjacentSectors()
{
    const int iMaxX = g_MapList.GetSectorCols(m_map);
    ASSERT(iMaxX > 0);
    const int iMaxY = g_MapList.GetSectorRows(m_map);
    ASSERT(iMaxY > 0);
    
    int iSectorCount = 0;
    for (int i = 0; i < m_map; ++i) // all sectors are stored in the same array, get a tmp count of all of the lower maps
    {
        if (!g_MapList.IsMapSupported(i))   // Skip disabled / unsupported maps
        {
            continue;
        }
        iSectorCount += g_MapList.GetSectorQty(i);
    }

    // Sectors are layed out in the array horizontally: when the row is complete (X), the subsequent sector is placed in
    //  the column below (Y).
    // Between each X coordinate there's a single sector index difference;
    //  between each Y coordinate there's a number of sectors equal to the sectors in a row.
    /*
      NW        N        NE
         y-1 | y-1 | y-1
         x-1 |     | x+1
        -----|-----|-----
             | my  |
      W  x-1 | pos | x+1  E
        -----|-----|-----
         y+1 | y+1 | y+1
         x-1 |     | x+1
      SW        S        SE
    */

    struct _xyDir_s { short x, y; };
    static constexpr _xyDir_s _xyDir[DIR_QTY]
    {
        {0, -1},    // N
        {+1,-1},    // NE
        {+1, 0},    // E
        {+1, +1},   // SE
        {0, +1},    // S
        {-1, +1},   // SW
        {-1, 0},    // W
        {-1, -1}    // NW
    };

    for (int i = 0; i < (int)DIR_QTY; ++i)
    {
        // out of bounds checks
		const int iAdjX = _x + _xyDir[i].x;
        if ((iAdjX < 0) || (iAdjX >= iMaxX))
            continue;

		const int iAdjY = _y + _xyDir[i].y;
        if ((iAdjY < 0) || (iAdjY >= iMaxY))
            continue;

		const int index = (iAdjY * iMaxX) + iAdjX;
        
        // This should not happen, because i did the checks above
        //if ((index < 0) || (index > iMaxSectors))
        //    continue;
        ASSERT((index >= 0) && (index <= g_MapList.GetSectorQty(m_map)));

        ASSERT(uint(iSectorCount + index) < g_World.m_SectorsQty);
        _ppAdjacentSectors[(DIR_TYPE)i] = g_World.m_Sectors[iSectorCount + index];
    }
}

CSector *CSectorBase::GetAdjacentSector(DIR_TYPE dir) const
{
    ASSERT(dir >= DIR_N && dir < DIR_QTY);
    return _ppAdjacentSectors[dir];
}

CSectorBase::CSectorBase() :
    _ppAdjacentSectors{}
{
	m_map = 0;
	m_index = 0;
	m_dwFlags = 0;
	_x = _y = -1;
}

void CSectorBase::Init(int index, uchar map, short x, short y)
{
	ADDTOCALLSTACK("CSectorBase::Init");
	if (!g_MapList.IsMapSupported(map) || !g_MapList.IsInitialized(map))
	{
		g_Log.EventError("Trying to initalize a sector %d in unsupported map #%d. Defaulting to 0,0.\n", index, map);
	}
	else if (( index < 0 ) || ( index >= g_MapList.GetSectorQty(map) ))
	{
		m_map = map;
		g_Log.EventError("Trying to initalize a sector by sector number %d out-of-range for map #%d. Defaulting to 0,%d.\n", index, map, map);
	}
	else
	{
        ASSERT(x >= 0 && y >= 0);
		m_index = index;
		m_map = map;
        _x = x;
        _y = y;
	}
}

bool CSectorBase::IsInDungeon() const
{
	ADDTOCALLSTACK("CSectorBase::IsInDungeon");
	// What part of the maps are filled with dungeons.
	// Used for light / weather calcs.
	CRegion *pRegion = GetRegion(GetBasePoint(), REGION_TYPE_AREA);

	return ( pRegion && pRegion->IsFlag(REGION_FLAG_UNDERGROUND) );
}

CRegion * CSectorBase::GetRegion( const CPointBase & pt, dword dwType ) const
{
	ADDTOCALLSTACK_INTENSIVE("CSectorBase::GetRegion");
	// Does it match the mask of types we care about ?
	// Assume sorted so that the smallest are first.
	//
	// REGION_TYPE_AREA => RES_AREA = World region area only = CRegionWorld
	// REGION_TYPE_ROOM => RES_ROOM = NPC House areas only = CRegion.
	// REGION_TYPE_MULTI => RES_WORLDITEM = UID linked types in general = CRegionWorld

	size_t iQty = m_RegionLinks.size();
	for ( size_t i = 0; i < iQty; ++i )
	{
		CRegion * pRegion = m_RegionLinks[i];
		ASSERT(pRegion);

        const CResourceID& ridRegion = pRegion->GetResourceID();
		ASSERT( ridRegion.IsValidUID());
		if ( ridRegion.IsUIDItem())
		{
			const CItemShip * pShipItem = dynamic_cast <CItemShip *>(ridRegion.ItemFindFromResource());
			if (pShipItem)
			{
				if (!(dwType & REGION_TYPE_SHIP))
					continue;
			}
			else if (!(dwType & REGION_TYPE_HOUSE))
				continue;
		}
		else if ( ridRegion.GetResType() == RES_AREA )
		{
			if ( ! ( dwType & REGION_TYPE_AREA ))
				continue;
		}
		else
		{
			if ( ! ( dwType & REGION_TYPE_ROOM ))
				continue;
		}

		if ( pRegion->m_pt.m_map != pt.m_map )
			continue;
		if ( ! pRegion->IsInside2d( pt ))
			continue;
		return pRegion;
	}
	return nullptr;
}

// Balkon: get regions list (to cycle through intercepted house regions)
size_t CSectorBase::GetRegions( const CPointBase & pt, dword dwType, CRegionLinks *pRLinks ) const
{
	ADDTOCALLSTACK_INTENSIVE("CSectorBase::GetRegions");
	size_t iQty = m_RegionLinks.size();
	for ( size_t i = 0; i < iQty; ++i )
	{
		CRegion * pRegion = m_RegionLinks[i];
		ASSERT(pRegion);

        const CResourceID& ridRegion = pRegion->GetResourceID();
		ASSERT(ridRegion.IsValidUID());
		if (ridRegion.IsUIDItem())
		{
			const CItemShip * pShipItem = dynamic_cast <const CItemShip *>(ridRegion.ItemFindFromResource());
			if (pShipItem)
			{
				if (!(dwType & REGION_TYPE_SHIP))
					continue;
			}
			else if (!(dwType & REGION_TYPE_HOUSE))
				continue;
		}
		else if (ridRegion.GetResType() == RES_AREA )
		{
			if ( ! ( dwType & REGION_TYPE_AREA ))
				continue;
		}
		else
		{
			if ( ! ( dwType & REGION_TYPE_ROOM ))
				continue;
		}

		if ( pRegion->m_pt.m_map != pt.m_map )
			continue;
		if ( ! pRegion->IsInside2d( pt ))
			continue;
        pRLinks->push_back(pRegion);
	}
	return pRLinks->size();
}

bool CSectorBase::UnLinkRegion( CRegion * pRegionOld )
{
	ADDTOCALLSTACK("CSectorBase::UnLinkRegion");
	if ( !pRegionOld )
		return false;
    auto it = std::find(m_RegionLinks.begin(), m_RegionLinks.end(), pRegionOld);
    if (it == m_RegionLinks.end())
        return false;
    m_RegionLinks.erase(it);
    return true;
}

bool CSectorBase::LinkRegion( CRegion * pRegionNew )
{
	ADDTOCALLSTACK("CSectorBase::LinkRegion");
	// link in a region. may have just moved !
	// Make sure the smaller regions are first in the array !
	// Later added regions from the MAP file should be the smaller ones, 
	//  according to the old rules.
	ASSERT(pRegionNew);
	ASSERT( pRegionNew->IsOverlapped(GetRect()) );
	size_t iQty = m_RegionLinks.size();

	for ( size_t i = 0; i < iQty; ++i )
	{
		CRegion * pRegion = m_RegionLinks[i];
		ASSERT(pRegion);
		if ( pRegionNew == pRegion )
		{
			DEBUG_ERR(( "region already linked!\n" ));
			return false;
		}

		if ( pRegion->IsOverlapped(pRegionNew))
		{
			// NOTE : We should use IsInside() but my version isn't completely accurate for it's FALSE return
			if ( pRegion->IsEqualRegion( pRegionNew ))
			{
				DEBUG_ERR(( "Conflicting region!\n" ));
				return false;
			}

			// it is accurate in the TRUE case.
			if ( pRegionNew->IsInside(pRegion))
				continue;

			// keep item (multi) regions on top
			if ( pRegion->GetResourceID().IsUIDItem() && !pRegionNew->GetResourceID().IsUIDItem() )
				continue;

			// must insert before this.
			m_RegionLinks.emplace(m_RegionLinks.begin() + i, pRegionNew);
			return true;
		}
	}

	m_RegionLinks.push_back(pRegionNew);
	return true;
}

CTeleport * CSectorBase::GetTeleport( const CPointMap & pt ) const
{
	ADDTOCALLSTACK("CSectorBase::GetTeleport");
	// Any teleports here at this point ?

	size_t i = m_Teleports.FindKey(pt.GetPointSortIndex());
	if ( i == SCONT_BADINDEX )
		return nullptr;

	CTeleport *pTeleport = static_cast<CTeleport *>(m_Teleports[i]);
	if ( pTeleport->m_map != pt.m_map )
		return nullptr;
	if ( abs(pTeleport->m_z - pt.m_z) > 5 )
		return nullptr;

	return pTeleport;
}

bool CSectorBase::AddTeleport( CTeleport * pTeleport )
{
	ADDTOCALLSTACK("CSectorBase::AddTeleport");
	// NOTE: can't be 2 teleports from the same place !
	// ASSERT( Teleport is actually in this sector !

	size_t i = m_Teleports.FindKey( pTeleport->GetPointSortIndex());
	if ( i != SCONT_BADINDEX )
	{
		DEBUG_ERR(( "Conflicting teleport %s!\n", pTeleport->WriteUsed() ));
		return false;
	}
	m_Teleports.AddSortKey( pTeleport, pTeleport->GetPointSortIndex());
	return true;
}

bool CSectorBase::IsFlagSet( dword dwFlag ) const
{
	return (( m_dwFlags & dwFlag) ? true : false );
}

CPointMap CSectorBase::GetBasePoint() const
{
	ADDTOCALLSTACK_INTENSIVE("CSectorBase::GetBasePoint");
	// What is the coord base of this sector. upper left point.
	ASSERT( m_index >= 0 && m_index < g_MapList.GetSectorQty(m_map) );
    const int iCols = g_MapList.GetSectorCols(m_map);
    const int iSize = g_MapList.GetSectorSize(m_map);
	CPointMap pt(
        (short)((m_index % iCols) * iSize),
		(short)((m_index / iCols) * iSize),
		0,
		m_map);
	return pt;
}

CRectMap CSectorBase::GetRect() const
{
    ADDTOCALLSTACK_INTENSIVE("CSectorBase::GetRect");
	// Get a rectangle for the sector.
	const CPointMap& pt = GetBasePoint();
    const int iSectorSize = g_MapList.GetSectorSize(pt.m_map);
	CRectMap rect;
	rect.m_left = pt.m_x;
	rect.m_top = pt.m_y;
	rect.m_right = pt.m_x + iSectorSize;	// East
	rect.m_bottom = pt.m_y + iSectorSize;	// South
	rect.m_map = pt.m_map;
	return rect;
}
