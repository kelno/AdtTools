#ifndef MCNK_H
#define MCNK_H

#include "chunkHeader.h"
#include "MCIN.h"

#include "MCVT.h"
#include "MCNR.h"
#include "MCLY.h"
#include "MCRF.h"
#include "MCAL.h"
#include "MCSH.h"
#include "MCSE.h"
#include "MCLQ.h"
#include "MCCV.h"

struct MCNKHeader // --schlumpf_ 17:01, 10 August 2009 (CEST), based on: 03-29-2005 By ObscuR, 11-08-2008 by Tharo
{
/*0x000*/  unsigned int flags;
/*0x004*/  unsigned int IndexX;
/*0x008*/  unsigned int IndexY;
/*0x00C*/  unsigned int nLayers;				// maximum 4
/*0x010*/  unsigned int nDoodadRefs;
/*0x014*/  unsigned int ofsMCVT;
/*0x018*/  unsigned int ofsMCNR;
/*0x01C*/  unsigned int ofsMCLY;
/*0x020*/  unsigned int ofsMCRF;
/*0x024*/  unsigned int ofsMCAL;
/*0x028*/  unsigned int sizeAlpha;
/*0x02C*/  unsigned int ofsMCSH;				// only with flags&0x1
/*0x030*/  unsigned int sizeShadow;
/*0x034*/  unsigned int areaid;
/*0x038*/  unsigned int nMapObjRefs;
/*0x03C*/  unsigned int holes;
/*0x040*/  char ReallyLowQualityTextureingMap[16];	// It is used to determine which detail doodads to show. Values are an array of two bit unsigned integers, naming the layer.
/*0x050*/  unsigned int predTex;				// 03-29-2005 By ObscuR; TODO: Investigate
/*0x054*/  unsigned int noEffectDoodad;				// 03-29-2005 By ObscuR; TODO: Investigate
/*0x058*/  unsigned int ofsMCSE;
/*0x05C*/  unsigned int nSndEmitters;				//will be set to 0 in the client if ofsSndEmitters doesn't point to MCSE!
/*0x060*/  unsigned int ofsMCLQ;
/*0x064*/  unsigned int sizeLiquid;  			// 8 when not used; only read if >8.
/*0x068*/  float position[3];
/*0x074*/  unsigned int ofsMCCV; 				// only with flags&0x40, had unsigned int textureId; in ObscuR's structure.
/*0x078*/  unsigned int unused1; 				// ofsMCLV introduced in Cataclysm
/*0x07C*/  unsigned int unused2; 			                              
/*0x080*/
};

//a chaque edit qui change la taille changer le mcin
class MCNK {
public:
	//unsigned int totalSize;
	MCIN* mcin;
    struct MCNKEntry {
		MCNKHeader header;
		MCVT* mcvt; 
		MCNR* mcnr;
		MCLY* mcly;
		MCRF* mcrf;
		MCSH* mcsh;
		MCAL* mcal;
		MCSE* mcse;
		MCLQ* mclq;
		MCCV* mccv;
	} entries[16*16];

	MCNK(std::fstream& adtFile, MCIN* mcin);
	friend std::ostream& operator<< (std::ostream &stream, MCNK& me);
};

enum MCNK_flags
{
	MCNK_FLAG_MCSH = 1,
	MCNK_FLAG_IMPASS = 2,
	MCNK_FLAG_LQ_RIVER = 4,
	MCNK_FLAG_LQ_OCEAN = 8,
	MCNK_FLAG_LQ_MAGMA = 16,
	MCNK_FLAG_MCCV = 32
};

#endif