#ifndef MTXF_H
#define MTXF_H

#include "chunkHeader.h"

struct MTXFEntry
{
    unsigned int flags;
};

class MTXF : public IntArrayChunk
{
public:
    MTXF(std::fstream& adtFile, unsigned int startByte) 
        : IntArrayChunk(adtFile, startByte)
    { }

    friend std::ostream& operator<< (std::ostream &stream, MTXF& me)
    {
        ChunkHeader CHeader("MTXF", me.size);
        stream << CHeader;
        stream << *(IntArrayChunk*)(&me);

        return stream;
    }
};

#endif