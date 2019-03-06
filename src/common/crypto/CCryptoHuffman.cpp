#include "../../sphere/threads.h"
#include "CCrypto.h"


// Huffman compression. Used to compress the outgoing data (packets sent from server to client).

const word CHuffman::sm_xCompress_Base[COMPRESS_TREE_SIZE] =	// static
{
	// The "golden" key for (0.0.0.0)
	// lowest 4 bits is the length. other source uses 2 int's per word here.
	// @ 014b389 in 2.0.3
	// @ 010a3d8 in 2.0.4
	0x0002, 0x01f5, 0x0226, 0x0347, 0x0757, 0x0286, 0x03b6, 0x0327,
	0x0e08, 0x0628, 0x0567, 0x0798, 0x19d9, 0x0978, 0x02a6, 0x0577,
	0x0718, 0x05b8, 0x1cc9, 0x0a78, 0x0257, 0x04f7, 0x0668, 0x07d8,
	0x1919, 0x1ce9, 0x03f7, 0x0909, 0x0598, 0x07b8, 0x0918, 0x0c68,
	0x02d6, 0x1869, 0x06f8, 0x0939, 0x1cca, 0x05a8, 0x1aea, 0x1c0a,
	0x1489, 0x14a9, 0x0829, 0x19fa, 0x1719, 0x1209, 0x0e79, 0x1f3a,
	0x14b9, 0x1009, 0x1909, 0x0136, 0x1619, 0x1259, 0x1339, 0x1959,
	0x1739, 0x1ca9, 0x0869, 0x1e99, 0x0db9, 0x1ec9, 0x08b9, 0x0859,
	0x00a5, 0x0968, 0x09c8, 0x1c39, 0x19c9, 0x08f9, 0x18f9, 0x0919,
	0x0879, 0x0c69, 0x1779, 0x0899, 0x0d69, 0x08c9, 0x1ee9, 0x1eb9,
	0x0849, 0x1649, 0x1759, 0x1cd9, 0x05e8, 0x0889, 0x12b9, 0x1729,
	0x10a9, 0x08d9, 0x13a9, 0x11c9, 0x1e1a, 0x1e0a, 0x1879, 0x1dca,
	0x1dfa, 0x0747, 0x19f9, 0x08d8, 0x0e48, 0x0797, 0x0ea9, 0x0e19,
	0x0408, 0x0417, 0x10b9, 0x0b09, 0x06a8, 0x0c18, 0x0717, 0x0787,
	0x0b18, 0x14c9, 0x0437, 0x0768, 0x0667, 0x04d7, 0x08a9, 0x02f6,
	0x0c98, 0x0ce9, 0x1499, 0x1609, 0x1baa, 0x19ea, 0x39fa, 0x0e59,
	0x1949, 0x1849, 0x1269, 0x0307, 0x06c8, 0x1219, 0x1e89, 0x1c1a,
	0x11da, 0x163a, 0x385a, 0x3dba, 0x17da, 0x106a, 0x397a, 0x24ea,
	0x02e7, 0x0988, 0x33ca, 0x32ea, 0x1e9a, 0x0bf9, 0x3dfa, 0x1dda,
	0x32da, 0x2eda, 0x30ba, 0x107a, 0x2e8a, 0x3dea, 0x125a, 0x1e8a,
	0x0e99, 0x1cda, 0x1b5a, 0x1659, 0x232a, 0x2e1a, 0x3aeb, 0x3c6b,
	0x3e2b, 0x205a, 0x29aa, 0x248a, 0x2cda, 0x23ba, 0x3c5b, 0x251a,
	0x2e9a, 0x252a, 0x1ea9, 0x3a0b, 0x391b, 0x23ca, 0x392b, 0x3d5b,
	0x233a, 0x2cca, 0x390b, 0x1bba, 0x3a1b, 0x3c4b, 0x211a, 0x203a,
	0x12a9, 0x231a, 0x3e0b, 0x29ba, 0x3d7b, 0x202a, 0x3adb, 0x213a,
	0x253a, 0x32ca, 0x23da, 0x23fa, 0x32fa, 0x11ca, 0x384a, 0x31ca,
	0x17ca, 0x30aa, 0x2e0a, 0x276a, 0x250a, 0x3e3b, 0x396a, 0x18fa,
	0x204a, 0x206a, 0x230a, 0x265a, 0x212a, 0x23ea, 0x3acb, 0x393b,
	0x3e1b, 0x1dea, 0x3d6b, 0x31da, 0x3e5b, 0x3e4b, 0x207a, 0x3c7b,
	0x277a, 0x3d4b, 0x0c08, 0x162a, 0x3daa, 0x124a, 0x1b4a, 0x264a,
	0x33da, 0x1d1a, 0x1afa, 0x39ea, 0x24fa, 0x373b, 0x249a, 0x372b,
	0x1679, 0x210a, 0x23aa, 0x1b8a, 0x3afb, 0x18ea, 0x2eca, 0x0627,
	0x00d4 // terminator
} ;

uint CHuffman::Compress( byte * pOutput, const byte * pInput, uint outLen, uint inLen ) // static
{
	ADDTOCALLSTACK("CHuffman::Compress");
	
    uint iLen = 0;
	int bitidx = 0;	    // Offset in output byte (xOutVal)
	byte xOutVal = 0;   // Don't bother to init this. It will just roll off all junk anyhow.


    for ( uint i = 0; i <= inLen; ++i )
	{
        word value = sm_xCompress_Base[ ( i == inLen ) ? (COMPRESS_TREE_SIZE - 1) : pInput[i] ];
		int nBits = value & 0xF;
		value >>= 4;
		while ( nBits-- )
		{
            if (iLen >= outLen)
                return 0; // error: i'm trying to write more bytes than the output buffer length
			xOutVal <<= 1;
			xOutVal |= (value >> nBits) & 0x1;
			if ( ++bitidx == 8)
			{
				bitidx = 0;
				pOutput[iLen++] = xOutVal;  
			}
		}
	}
	if (bitidx)	// flush odd bits.
	{
        if (iLen >= outLen)
            return 0;
		pOutput[iLen++] = xOutVal << (8 - bitidx);
	}
    
	return iLen;
}
