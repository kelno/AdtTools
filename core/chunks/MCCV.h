#ifndef MCCV_H
#define MCCV_H

#include "chunkHeader.h"

class MCCV 
{
public:
    std::vector<char> fill;
    unsigned int size;

    MCCV(std::fstream& adtFile, unsigned int startByte) 
    {
        adtFile.seekg(startByte);
        ChunkHeader CHeader(adtFile);
        size = CHeader.chunkSize;
        if (size)
        {
            fill.resize(size);
            adtFile.read(&fill[0], size);
        }
    }
    
    friend std::ostream& operator<< (std::ostream &stream, MCCV& me) 
    {
        ChunkHeader CHeader("MCCV", me.size);
        stream << CHeader;

        if (me.size)
            stream.write(&me.fill[0], me.size);

        return stream;
    }
};

#endif