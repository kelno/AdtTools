// filename starting position in MMDX chunk. These entries are getting referenced in the MDDF chunk.

#ifndef MMID_H
#define MMID_H

#include "IntArrayChunk.h"

class MMID : public IntArrayChunk
{
public:
    MMID(std::fstream& adtFile, unsigned int startByte)
        : IntArrayChunk(adtFile, startByte)
    { }

    friend std::ostream& operator<< (std::ostream &stream, MMID& me)
    {
        ChunkHeader CHeader("MMID", me.size);
        stream << CHeader;
        stream << *(IntArrayChunk*)(&me);

        return stream;
    }
};

#endif