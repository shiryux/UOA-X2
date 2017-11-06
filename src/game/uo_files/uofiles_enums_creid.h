/**
* @file uofiles_enums_creid.h
*
*/

#pragma once
#ifndef _INC_UOFILES_ENUMS_CREID_H
#define _INC_UOFILES_ENUMS_CREID_H

enum CREID_TYPE	// enum the creature animations. (dont allow any others !) also know as "model number"
{
	CREID_INVALID = 0,

/* ----	 Animations stored in the anim*.MUL files ----	*/
/* High detail critters */

	CREID_OGRE				= 0x1,
	CREID_ETTIN				= 0x2,
	CREID_ZOMBIE			= 0x3,
	CREID_GARGOYLE			= 0x4,
	CREID_EAGLE				= 0x5,
	CREID_BIRD				= 0x6,
	CREID_ORC_CAPTAIN		= 0x7,
	CREID_CORPSER			= 0x8,
	CREID_DAEMON			= 0x9,
	CREID_DAEMON_SWORD		= 0xA,
	CREID_DRAGON_GREY		= 0xC,
	CREID_AIR_ELEM			= 0xD,
	CREID_EARTH_ELEM		= 0xE,
	CREID_FIRE_ELEM			= 0xF,
	CREID_WATER_ELEM		= 0x10,
	CREID_ORC				= 0x11,
	CREID_ETTIN_AXE			= 0x12,
	CREID_GIANT_SNAKE		= 0x15,
	CREID_GAZER				= 0x16,
	CREID_LICH				= 0x18,
	CREID_SPECTRE			= 0x1A,
	CREID_GIANT_SPIDER		= 0x1C,
	CREID_GORILLA			= 0x1D,
	CREID_HARPY				= 0x1E,
	CREID_HEADLESS			= 0x1F,
	CREID_LIZMAN			= 0x21,
	CREID_LIZMAN_SPEAR		= 0x23,
	CREID_LIZMAN_MACE		= 0x24,
	CREID_MONGBAT			= 0x27,
	CREID_ORC_CLUB			= 0x29,
	CREID_RATMAN			= 0x2A,
	CREID_RATMAN_CLUB		= 0x2C,
	CREID_RATMAN_SWORD		= 0x2D,
	CREID_REAPER			= 0x2F,	// tree
	CREID_SCORPION_GIANT	= 0x30,
	CREID_SKELETON			= 0x32,
	CREID_SLIME				= 0x33,
	CREID_SNAKE				= 0x34,
	CREID_TROLL_SWORD		= 0x35,
	CREID_TROLL				= 0x36,
	CREID_TROLL_MACE		= 0x37,
	CREID_SKEL_AXE			= 0x38,
	CREID_SKEL_SW_SH		= 0x39,	// sword and shield
	CREID_WISP				= 0x3A,
	CREID_DRAGON_RED		= 0x3B,
	CREID_DRAKE_GREY		= 0x3C,
	CREID_DRAKE_RED			= 0x3D,
	CREID_COUGAR			= 0x3F,
	CREID_LEOPARD			= 0x40,
	CREID_LEOPARD_SNOW		= 0x41,
	CREID_GAZER_ELDER		= 0x44,
	CREID_GAZER2			= 0x45,	// broken anim?
	CREID_OGRE_LORD			= 0x53,
	//CREID_OGRE_LORD2		= 0x54,	// broken? duplicate?

	// T2A (The second age) monsters

	CREID_SWAMP_TANTACLES	= 0x42,
	CREID_GARG_STONE		= 0x43,
	CREID_TERA_WARRIOR		= 0x46,
	CREID_TERA_DRONE		= 0x47,
	CREID_TERA_MATRIARCH	= 0x48,
	CREID_HARPY_STONE		= 0x49,
	CREID_IMP				= 0x4A,
	CREID_TITAN				= 0x4B,
	CREID_CYCLOPS			= 0x4C,
	CREID_KRAKEN			= 0x4D,
	CREID_LICH_ANCIENT		= 0x4E,
	CREID_LICH_LORD			= 0x4F,
	CREID_GIANT_TOAD		= 0x50,
	CREID_BULL_FROG			= 0x51,

	CREID_OPHID_SHAMAN		= 0x55,
	CREID_OPHID_WARRIOR		= 0x56,
	CREID_OPHID_QUEEN		= 0x57,

	CREID_GOAT				= 0x58,

	CREID_SERPENT_ICE		= 0x59,
	CREID_SERPENT_LAVA		= 0x5A,
	CREID_SERPENT_SILVER	= 0x5B,
	CREID_SERPENT_COIL		= 0x5C,	// ml?
	CREID_SERPENT_ARROW		= 0x5D,	// what's that?
	CREID_OOZE_FROST		= 0x5E,
	CREID_SEA_CREATURE		= 0x5F,
	CREID_SLIME_CORROSIVE	= 0x60,
	CREID_HELLHOUND			= 0x61,	// ?
	CREID_HELLHOUND_LEAD	= 0x62,
	CREID_WOLF_DARK			= 0x63,
	CREID_WOLF_SILVER		= 0x64,
	CREID_CENTAUR			= 0x65,
	CREID_DEMON_EXODUS		= 0x66,
	CREID_DRAGON_SERPENTINE	= 0x67,
	CREID_DRAGON_SKELETAL	= 0x68,
	CREID_DRAGON_GREATER	= 0x69,
	CREID_WYRM_SHADOW		= 0x6A,

	CREID_ELEM_ORE_AGA		= 0x6B,
	CREID_ELEM_ORE_BRONZ	= 0x6C,
	CREID_ELEM_ORE_COPP		= 0x6D,
	CREID_ELEM_ORE_DCOPP	= 0x6E,
	CREID_ELEM_ORE_SHAD		= 0x6F,
	CREID_ELEM_ORE_VALO		= 0x70,
	CREID_ELEM_ORE_VERI		= 0x71,

	CREID_STEED_DARK		= 0x72,
	CREID_STEED_ETHEREAL	= 0x73,
	CREID_NIGHTMARE			= 0x74,
	CREID_STEED_SILVER		= 0x75,

	CREID_WARHORSE_BRIT		= 0x76,
	CREID_WARHORSE_MAGE		= 0x77,
	CREID_WARHORSE_MINAX	= 0x78,
	CREID_WARHORSE_SHAD		= 0x79,
	CREID_UNICORN			= 0x78,
	CREID_ETHEREAL_WARRIOR	= 0x79,

	CREID_THEOPHILUS		= 0x7C,
	CREID_EVILMAGE			= 0x7D,
	CREID_EVILMAGE_LORD		= 0x7E,
	CREID_HELLCAT			= 0x7F,
	CREID_PIXIE				= 0x80,
	CREID_HARROWER_TENT		= 0x81,

	CREID_EFREET			= 0x83,
	CREID_KIRIN				= 0x84,
	CREID_ALLIGATOR_SM		= 0x85,
	CREID_DRAGON_KOMODO		= 0x86,
	CREID_OGRE_LORD_ARCTIC	= 0x87,
	CREID_OPHIDIAN_JUSTICAR	= 0x88,
	CREID_OPHIDIAN_AVENGER	= 0x89,
	CREID_ORC_LORD			= 0x8A,
	CREID_ORC_CHOPPER		= 0x8B,
	CREID_ORC_MAGE			= 0x8C,

	CREID_RATMAN_ARCHER		= 0x8E,
	CREID_RATMAN_MAGE		= 0x8F,
	CREID_HORSE_SEA			= 0x90,	// ?
	CREID_SEA_SERPENT_DEEP	= 0x91,
	CREID_HARROWER			= 0x92,
	CREID_SKELETON_KNIGHT	= 0x93,
	CREID_SKELETON_MAGE		= 0x94,
	CREID_SUCCUBUS			= 0x95,

	// LBR (Lord Blackthorn's revenge) monsters

	CREID_SPIDER_MALEFIC	= 0x13,
	CREID_SERPENTINE_DRAGON = 0x67,
	CREID_SKELETAL_DRAGON	= 0x68,

	CREID_SEA_SERP			= 0x96,
	CREID_DOLPHIN			= 0x97,

	CREID_GHOUL				= 0x99,
	CREID_MUMMY				= 0x9A,
	CREID_ROTTING_CORPSE	= 0x9B,
	CREID_TURKEY			= 0x9C,
	CREID_LADY_LISSITH		= 0x9D, // giant black widow
	CREID_ELEM_ACID			= 0x9E,
	CREID_ELEM_BLOOD		= 0x9F,
	CREID_ELEM_UNK			= 0xA0,
	CREID_ELEM_ICE			= 0xA1,
	CREID_ELEM_POISON		= 0xA2,
	CREID_ELEM_SNOW			= 0xA3,
	CREID_ENERGY_VORTEX		= 0xA4,	// GOOD?
	CREID_WISP_DARK			= 0xA5,

	CREID_ELEM_ORE_GOLD		= 0xA6,

	CREID_BEAR_BROWN		= 0xA7,
	CREID_SHADOW_FIEND		= 0xA8,
	CREID_BEETLE_FIRE		= 0xA9,
	CREID_LLAMA_ETH			= 0xAA,
	CREID_OSTARD_FRENZ_ETH	= 0xAB,
	CREID_CHAMP_RIKKTOR		= 0xAC,
	CREID_CHAMP_MEPHITIS	= 0xAD,
	CREID_CHAMP_SEMIDAR		= 0xAE,
	CREID_CHAMP_OAKS		= 0xAF,
	CREID_CHAMP_SILVANI		= 0xB0,
	CREID_WARHORSE_DREAD	= 0xB1,
	CREID_MARE_UNK1			= 0xB2,
	CREID_MARE_UNK2			= 0xB3,
	CREID_WYRM_WHITE_UNK	= 0xB4,
	CREID_ORC_SCOUT			= 0xB5,
	CREID_ORC_BOMBER		= 0xB6,

	CREID_RIDGEBACK			= 0xBB,
	CREID_RIDGEBACK_SAVAGE	= 0xBC,
	CREID_ORC_BRUTE			= 0xBD,
	CREID_STEED_FIRE		= 0xBE,
	CREID_KIRIN_ETH			= 0xBF,	// ?
	CREID_UNICORN_ETH		= 0xC0,
	CREID_RIDGEBACK_ETH		= 0xC1,
	CREID_SWAMP_DRAGON_ETH	= 0xC2,
	CREID_GIANT_BEETLE_ETH	= 0xC3,

	CREID_IRON_GOLEM		= 0x2F0,

	CREID_JUKA_WARRIOR		= 0x2FC,
	CREID_JUKA_MAGE			= 0x2FD,
	CREID_JUKA_LORD			= 0x2FE,
	CREID_BETRAYER			= 0x2FF,
	CREID_JUGGERNAUT		= 0x300,

	CREID_MEER_MAGE			= 0x302,
	CREID_MEER_WARRIOR		= 0x303,
	CREID_MEER_ETERNAL		= 0x304,
	CREID_MEER_CAPTAIN		= 0x305,
	CREID_DAWN				= 0x306,
	CREID_PLAGUE_BEAST		= 0x307,
	CREID_HORDE_DEMON_MINION= 0x308,
	CREID_DOPPLEGANGER		= 0x309,
	CREID_GAZER_LARVA		= 0x30A,
	CREID_BOGLING			= 0x30B,
	CREID_BOG_THING			= 0x30C,
	CREID_SOLEN_WORKER		= 0x30D,
	CREID_SOLEN_WARRIOR		= 0x30E,
	CREID_SOLEN_QUEEN		= 0x30F,
	CREID_DEMON_ARCANE		= 0x310,
	CREID_DEMON_MOLOCH		= 0x311,
	CREID_ANT_LION			= 0x313,
	CREID_SPHYNX			= 0x314,
	CREID_QUAGMIRE			= 0x315,
	CREID_ELEM_SAND_VORTEX	= 0x316,
	CREID_GIANT_BEETLE		= 0x317,
	CREID_DEMON_CHAOS		= 0x318,
	CREID_SKELETAL_MOUNT	= 0x319,
	CREID_SWAMP_DRAGON		= 0x31A,
	CREID_HORDE_DEMON_L		= 0x31C,
	CREID_REPTILE_LORD		= 0x31D,
	CREID_ANCIENT_WYRM		= 0x31E,
	CREID_SWAMP_DRAGON_AR	= 0x31F, // Armored swamp dragon

	CREID_MULTICOLORED_HORDE_DEMON = 0x3e7,

	// AOS (Age of Shadows) monsters

	CREID_WYVERN			= 0x3E,
	CREID_DARK_GUARDIAN		= 0x52, // ?

	CREID_ELEM_CRYSTAL		= 0X12C,
	CREID_SKITTERING_HOPPER	= 0x12E,
	CREID_DEVOURER_SOULS	= 0x12F,
	CREID_FLESH_GOLEM		= 0x130,
	CREID_GORE_FIEND		= 0x131,
	CREID_IMPALER			= 0x132,
	CREID_GIBBERLING		= 0x133,
	CREID_BONE_DAEMON		= 0x134,
	CREID_PATCHW_SKELETON	= 0x135, // patchwork skeleton
	CREID_BANSHEE_WAILING	= 0x136,
	CREID_SHADOW_KNIGHT		= 0x137,
	CREID_ABYSSMAL_HORROR	= 0x138,
	CREID_DARKNIGHT_CREEPER	= 0x139,
	CREID_RAVAGER			= 0x13A,
	CREID_FLESH_RENDERER	= 0x13B,
	CREID_WANDERER_VOID		= 0x13C,
	CREID_VAMPIRE_BAT		= 0x13D,
	CREID_DARK_FATHER		= 0x13E,
	CREID_MOUND_MAGGOTS		= 0x13F,
	CREID_REPTALON			= 0x114,
	CREID_CU_SIDHE			= 0x115,
	CREID_SQUIRREL			= 0x116,
	CREID_FERRET			= 0x117,
	CREID_MINOTAUR_CAPTAIN	= 0x118,
	CREID_MINOTAUR_SCOUT	= 0x119,
	CREID_PARROT			= 0x11A,
	CREID_BIRD_CROW			= 0x11B,
	CREID_STEED_ARMORED		= 0x11C,
	CREID_REAPER_REDUX		= 0x11D,
	CREID_REVENANT			= 0x2EE,
	CREID_HORRIFIC_BEAST	= 0x2EA,	// moloch duplicate?
	CREID_REAPER_FORM		= 0xE6,
	CREID_SPECTRAL_ARMOR	= 0x27D,

	// ML (Mondain's Legacy) monsters

	CREID_KAZE_KEMONO		= 0xC4,
	CREID_RAI_JU			= 0xC7,
	CREID_KAPPA				= 0xF0,
	CREID_ONI				= 0xF1,
	CREID_DEATHWATCH_BEETLE	= 0xF2,
	CREID_HIRYU				= 0xF3,
	CREID_RUNE_BEETLE		= 0xF4,
	CREID_YOMOTSU_WARRIOR	= 0xF5,
	CREID_BAKE_KITSUNE		= 0xF6,
	CREID_FAN_DANCER		= 0xF7,
	CREID_GAMAN				= 0xF8,
	CREID_YAMANDON			= 0xF9,
	CREID_TSUKI_WOLF		= 0xFA,
	CREID_REVENANT_LION		= 0xFB,
	CREID_LADY_SNOW			= 0xFC,
	CREID_YOMOTSU_PRIEST	= 0xFD,
	CREID_CRANE				= 0xFE,
	CREID_YOMOTSU_ELDER		= 0xFF,
	CREID_CHIEF_PAROXYSMUS	= 0x100,
	CREID_DREAD_HORN		= 0x101,
	CREID_LADY_MELISANDE	= 0x102,
	CREID_MONSTROUS_I_G		= 0x103, // monstrous interred grizzle
	CREID_MANTRA_EFF		= 0x104, // mantra effervescent
	CREID_SHIMMERING_EFF	= 0x105, // shimmering effusion
	CREID_MINOTAUR_TORM		= 0x106, // tormented minotaur
	CREID_MINOTAUR			= 0x107,
	CREID_CHANGELING		= 0x108,
	CREID_HYDRA				= 0x109,
	CREID_DRYAD				= 0x10A,
	CREID_SATYR				= 0x10F,
	CREID_CORPOREAL_BRUME	= 0x110,
	CREID_FETID_ESSENCE		= 0x111,
	CREID_TIME_LORD			= 0x2B1,
	CREID_SHADOW_LORD		= 0x2C0,


	// ---- Animals (Low detail critters) ----

	CREID_HORSE_TAN			= 0xC8,	// white = 200 decinal
	CREID_CAT				= 0xc9,
	CREID_ALLIGATOR			= 0xCA,
	CREID_PIG				= 0xCB,
	CREID_HORSE_BROWN_DK	= 0xCC,
	CREID_RABBIT			= 0xCD,
	CREID_LIZARD_LAVA		= 0xce,
	CREID_SHEEP				= 0xCF,	// un-sheered.
	CREID_CHICKEN			= 0xD0,
	CREID_GOAT_MOUNTAIN		= 0xD1,
	CREID_OSTARD_DESERT		= 0xD2,	// T2A = Desert Ostard (ridable)
	CREID_BEAR_BLACK		= 0xD3,
	CREID_BEAR_GRIZZLY		= 0xD4,
	CREID_BEAR_POLAR		= 0xD5,
	CREID_PANTHER			= 0xD6,
	CREID_RAT_GIANT			= 0xD7,
	CREID_COW_BW			= 0xD8,
	CREID_DOG				= 0xD9,
	CREID_OSTARD_FRENZ		= 0xDA,	// Frenzied Ostard
	CREID_OSTARD_FOREST		= 0xDB,	// Forest Ostard
	CREID_LLAMA				= 0xDC,
	CREID_WALRUS			= 0xDD,
	CREID_SHEEP_SHORN		= 0xDF,
	CREID_WOLF_TIMBER		= 0xE1,
	CREID_HORSE_GRAY		= 0xE2,
	CREID_HORSE_BROWN_LT	= 0xE4,
	CREID_COW_BROWN			= 0xE7,
	CREID_BULL_BROWN_LT		= 0xE8,	// light brown
	CREID_BULL_BROWN_DK		= 0xE9,	// dark brown
	CREID_HART				= 0xEA,	// Male deer
	CREID_DEER				= 0xED,
	CREID_RAT				= 0xEE,
	CREID_BOAR				= 0x122, // large pig
	CREID_HORSE_PACK		= 0x123, // Pack horse with saddle bags
	CREID_LLAMA_PACK		= 0x124, // Pack llama with saddle bags


	// ---- Humans / Gargoyles / Equipment ----

	CREID_MAN				= 0x190, // 400 decimal
	CREID_WOMAN				= 0x191,
	CREID_GHOSTMAN			= 0x192, // Ghost robe is not automatic !
	CREID_GHOSTWOMAN		= 0x193,

	CREID_VORTEX			= 0x23d, // T2A = vortex
	CREID_BLADES			= 0x23e, // blade spirits (in human range? not sure why)
		 
	CREID_ELFMAN			= 0x25D, // 605 decimal
	CREID_ELFWOMAN			= 0x25E,
	CREID_ELFGHOSTMAN		= 0x25F,
	CREID_ELFGHOSTWOMAN		= 0x260,

	CREID_GARGMAN			= 0x29A, // 666 decimal
	CREID_GARGWOMAN			= 0x29B,
	CREID_GARGGHOSTMAN		= 0x2B6, // 694
	CREID_GARGGHOSTWOMAN	= 0x2B7,

	//..
	
	CREID_MAN_PALADIN		= 0x8D,
	CREID_EQUIP_GM_ROBE		= 0x3DB,


/* ----	 Animations stored in the AnimationFrame*.UOP files ----	*/
	// SA (Stygian Abyss) monsters

	CREID_GARG_FIRE				= 0x82,
	CREID_DRAGON_CRIMSON		= 0xC5,
	CREID_DRAGON_PLATINUM		= 0xC6,
	CREID_TROGLODYTE			= 0x10B,
	CREID_GRUBBER				= 0x10E,
	CREID_BLOODWORM				= 0x11E,
	CREID_VOLLEM				= 0x125,
	CREID_GOBLIN_GRAY			= 0x14E,
	CREID_BOURA_ARMORED			= 0x1B0,
	CREID_STONE_FORM			= 0x2C1,
	CREID_ABYSSAL_INFERNAL		= 0x2C9,
	CREID_BEETLE_IRON			= 0x2CA,
	CREID_BOURA					= 0x2CB,
	CREID_CHICKEN_LIZARD		= 0x2CC,
	CREID_SCORPION_CLOCKWORK	= 0x2CD,
	CREID_DRAGON_FAIRY			= 0x2CE,
	CREID_DRAGON_WOLF			= 0x2CF,
	CREID_ELEM_LAVA				= 0x2D0,
	CREID_MADDENING_HORROR		= 0x2D1,
	CREID_GARG_UNDEAD			= 0x2D2,
	CREID_GOBLIN_GREEN			= 0x2D3,
	CREID_GOBLIN_GREEN_MAGE		= 0x2D4,
	CREID_HOMUNCULUS			= 0x2D5,
	CREID_KEPETCH				= 0x2D6,
	CREID_KEPETCH_SHORN			= 0x2D7,
	CREID_MEDUSA				= 0x2D8,
	CREID_MIMIC					= 0x2D9,
	CREID_RAPTOR				= 0x2DA,
	CREID_ROTWORM				= 0x2DC,
	CREID_SKREE					= 0x2DD,
	CREID_SLITH					= 0x2DE,
	CREID_NAVREY_NIGHT_EYES		= 0x2DF,
	CREID_SPIDER_WOLF			= 0x2E0,
	CREID_SPIDER_TRAPDOOR		= 0x2E1,
	CREID_FIRE_ANT				= 0x2E2,
	CREID_WOLF_LEATHER			= 0x2E3,
	CREID_DREAM_WRAITH			= 0x2E4,
	CREID_SLASHER_VEILS			= 0x2E5,
	CREID_VAMPIRE				= 0x2E8,
	CREID_VAMPIRE_FEMALE		= 0x2E9,
	CREID_GARG_ENSLAVED			= 0x2F1,
	CREID_TURKEY_GIANT 			= 0x402,

	// HS (High Seas) monsters
	CREID_SCALIS 				= 0x42C,
	CREID_HELLHOUND_ANCIENT 	= 0x42D,
	CREID_WEREWOLF 				= 0x42E,
	CREID_MINOTAUR_LORD 		= 0x42F,
	CREID_CHARYBDIS 			= 0x4DC,
	CREID_CHARYBDIS_TENTACLE 	= 0x4DD,
	CREID_PUMPKIN_DEMON 		= 0x4DE,
	CREID_PUMPKIN_FRIGHT 		= 0x4DF,
	CREID_CLOCKWORK_EXODUS 		= 0x4E0,
	CREID_LORD_BLACKTHORN 		= 0x4E5,

	// TOL (Time of Legends) monsters
	CREID_WILD_TIGER 			= 0x4E6,
	CREID_TIGER_ETHEREAL 		= 0x4E7,
	CREID_DIMETROSAUR 			= 0x505,
	CREID_GALLUSAURUS 			= 0x506,
	CREID_ARCHAEOSAURUS 		= 0x507,
	CREID_DRAGON_TURTLE 		= 0x508,
	CREID_NAJASAURUS 			= 0x509,
	CREID_ALLOSAURUS 			= 0x50A,
	CREID_SAUROSAURUS 			= 0x50B,
	CREID_ANCHISAUR 			= 0x50C,
	CREID_MYRMIDEX_LARVAE 		= 0x50D,
	CREID_DRAGON_TURTLE_HATCHL	= 0x50E, // dragon turtle hatchling
	CREID_GIANT_GORILLA 		= 0x51C,
	CREID_TIGER_CUB 			= 0x51D,
	CREID_TYRANNOSAURUS_REX 	= 0x578,
	CREID_TARANTULA 			= 0x579,
	CREID_MYRMIDEX_DRONE 		= 0x57A,
	CREID_MYRMIDEX_WARRIOR 		= 0x57B,
	CREID_MYRMIDEX_QUEEN 		= 0x57C,
	CREID_ZIPACTRIOTL 			= 0x57D,
	CREID_KOTL_AUTOMATON 		= 0x57E,
	CREID_LASHER 				= 0x57F,
	CREID_HORSE_PALOMINO 		= 0x580,
	CREID_WINDRUNNER 			= 0x582,
	CREID_TRICERATOPS 			= 0x587,
	CREID_SABERTOOTHED_TIGER 	= 0x588,
	CREID_DRAKE_PLATINUM 		= 0x589,
	CREID_DRAKE_PLATINUM_ELEM	= 0x58A,
	CREID_DRAKE_CRIMSON 		= 0x58B,
	CREID_DRAKE_CRIMSON_ELEM	= 0x58C,
	CREID_DRAKE_STYGIAN 		= 0x58D,
	CREID_DRAKE_STYGIAN_ELEM	= 0x58E,
	CREID_BLOOD_FOX 			= 0x58F,
	CREID_FROST_MITE 			= 0x590,
	CREID_OSSEIN_RAM 			= 0x591,
	CREID_LION 					= 0x592,
	CREID_HYDROS 				= 0x593,
	CREID_JACK_IN_THE_BOX 		= 0x594,
	CREID_LITHOS 				= 0x597,
	CREID_STRATOS 				= 0x598,
	CREID_PYROS 				= 0x599,
	CREID_SERPENTINE_DRAGON_ETH = 0x59A,

/* ----	 Special ----	*/

	CREID_QTY		= 0x800,	// Max number of base character types, based on art work.

	// re-use animations to make other types on NPCS

	NPCID_SCRIPT	= 0x4000,	// Safe area for server specific NPC defintions.
	NPCID_QTY		= 0x8000,	// Spawn types start here.

	SPAWNTYPE_START = 0x8001
};


#endif //_INC_UOFILES_ENUMS_CREID_H
