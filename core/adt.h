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
    std::unique_ptr<MVER> mver;   //version (always 12h?)
    std::unique_ptr<MHDR> mhdr;   //header
    std::unique_ptr<MCIN> mcin;   //Pointers to MCNK chunks and their sizes.
    std::unique_ptr<MTEX> mtex;   //List of textures used for texturing the terrain in this map tile.
    std::unique_ptr<MMDX> mmdx;   //List of filenames for M2 models that appear in this map tile.
    std::unique_ptr<MMID> mmid;   //List of offsets of model filenames in the MMDX chunk.
    std::unique_ptr<MWMO> mwmo;   //List of filenames for WMOs (world map objects) that appear in this map tile.
    std::unique_ptr<MWID> mwid;   //List of offsets of WMO filenames in the MWMO chunk.
    std::unique_ptr<MDDF> mddf;   //Placement information for doodads (M2 models). Additional to this, the models to render are referenced in each MCRF chunk. 
    std::unique_ptr<MODF> modf;   //Placement information for WMOs. Additional to this, the WMOs to render are referenced in each MCRF chunk. (?) 
    std::unique_ptr<MH2O> mh2o;   //Water chunk (LK)
    std::unique_ptr<MCNK> mcnk;   //Terrain
    std::unique_ptr<MFBO> mfbo;   //A bounding box for flying.
    std::unique_ptr<MTXF> mtxf;   //Array of integers wich indicate if the same position in the MTEX array has to be handled differentely.

    adt(std::fstream& adtFile);

    void WriteToDisk(std::fstream& adtFile); 

    //MCLQ is the only water supported by <= BC clients (this is also retro-supported by later clients)
    void AllWaterMCLQ(float height, MCNKFlags flags = MCNKFlags::FLAG_LQ_RIVER);
private:
    std::vector<char> buffedAdtFile; //adt file
};

#endif