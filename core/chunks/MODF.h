#include "chunkHeader.h"

#ifndef MODF_H
#define MODF_H

/*
enum MODFFlags {
    modf_destroyable = 1,         // set for destroyable buildings like the tower in DeathknightStart. This makes it a server-controllable game object.
  };
*/
struct MODFEntry 
{
    unsigned int mwidEntry;           // references an entry in the MWID chunk, specifying the model to use.
    unsigned int uniqueId;            // this ID should be unique for all ADTs currently loaded. Best, they are unique for the whole map.
    float position[3];
    float rotation[3];            // same as in MDDF.
    float lowerBounds[3];         // these two are position plus the wmo bounding box.
    float upperBounds[3];         // they are used for defining when if they are rendered as well as collision.
    unsigned short flags;               // values from enum MODFFlags.
    unsigned short doodadSet;           // which WMO doodad set is used.
    unsigned short nameSet;             // which WMO name set is used. Used for renaming goldshire inn to northshire inn while using the same model.
    unsigned short padding;             // it reads only a WORD into the WMAPOBJDEF structure for name. I don't know about the rest.
};

class MODF 
{
public:
    unsigned int size;
    std::vector<MODFEntry> entries;

    MODF(std::fstream& adtFile, unsigned int startByte) 
    { 
        adtFile.seekg(startByte);
        ChunkHeader MODFHeader(adtFile);
        size = MODFHeader.chunkSize;
        unsigned int modfCount = size / sizeof(MODFEntry);
        if (size % sizeof(MODFEntry) != 0)
        {
            sLogger->Out(Logger::LOG_LEVEL_ERROR, "MODF has a size that's not a multiple of sizeof(MODFEntry), skipping remaining bytes");
            size = modfCount * sizeof(MODFEntry);
        }

        entries.resize(modfCount);
        for (unsigned int i = 0; i < modfCount; ++i)
            adtFile.read(reinterpret_cast<char*>(&entries[i]), sizeof(MODFEntry));
    }

    friend std::ostream& operator<< (std::ostream &stream, MODF& me)
    {
        ChunkHeader CHeader("MODF", me.size);
        stream << CHeader;
        stream.write(reinterpret_cast<char*>(&me.entries[0]), me.size);

        return stream;
    }
};

#endif