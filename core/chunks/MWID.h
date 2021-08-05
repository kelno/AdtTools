// filename starting position in MWMO chunk. These entries are getting referenced in the MODF chunk.
#ifndef MWID_H
#define MWID_H

#include "IntArrayChunk.h"

class MWID : public IntArrayChunk
{
public:
    MWID(std::fstream& adtFile, unsigned int startByte) 
        : IntArrayChunk(adtFile, startByte)
    { }

    friend std::ostream& operator<< (std::ostream &stream, MWID& me)
    {
        ChunkHeader CHeader("MWID", me.size);
        stream << CHeader;
        stream << *(IntArrayChunk*)(&me);

        return stream;
    }
};

#endif