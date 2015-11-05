/* 
TODO : Parsemer le tout d'exceptions ! Faut que ça soit robuste aux fichiers screwed
*/
#ifndef ADT_H
#define ADT_H

#define AUTHOR "Kelno <dr.kelno@gmail.com>"

#include <fstream>
#include <iostream>

#include "chunkHeader.h"
#include "MVER.h"
#include "MHDR.h"
#include "MCIN.h"
#include "MTEX.h"
#include "MMDX.h"
#include "MMID.h"
#include "MWMO.h"
#include "MWID.h"
#include "MDDF.h"
#include "MODF.h"
#include "MH2O.h"
#include "MCNK.h"
#include "MFBO.h"
#include "MTXF.h"

class adt {
public:
    MVER* mver = nullptr;   //version (always 12h?)
	MHDR* mhdr = nullptr;   //header
    MCIN* mcin = nullptr;   //Pointers to MCNK chunks and their sizes.
    MTEX* mtex = nullptr;   //List of textures used for texturing the terrain in this map tile.
    MMDX* mmdx = nullptr;   //List of filenames for M2 models that appear in this map tile.
    MMID* mmid = nullptr;   //List of offsets of model filenames in the MMDX chunk.
    MWMO* mwmo = nullptr;   //List of filenames for WMOs (world map objects) that appear in this map tile.
    MWID* mwid = nullptr;   //List of offsets of WMO filenames in the MWMO chunk.
    MDDF* mddf = nullptr;   //Placement information for doodads (M2 models). Additional to this, the models to render are referenced in each MCRF chunk. 
    MODF* modf = nullptr;   //Placement information for WMOs. Additional to this, the WMOs to render are referenced in each MCRF chunk. (?) 
    MH2O* mh2o = nullptr;   //Water chunk (LK)
    MCNK* mcnk = nullptr;   //Terrain
	MFBO* mfbo = nullptr;   //A bounding box for flying.
    MTXF* mtxf = nullptr;   //Array of integers wich indicate if the same position in the MTEX array has to be handled differentely.

	//void* fileChunks[14]; //on connait le type grace à la position

	adt(std::fstream& adtFile);
    ~adt();

	void WriteToDisk(std::fstream& adtFile); 

    //MCLQ is the only water supported by <= BC clients (this is also retro-supported by later clients)
    void AllWaterMCLQ(float height);
private:
    std::vector<char> buffedAdtFile; //adt file
};

#endif