#ifndef MCSE_H
#define MCSE_H

#include "chunkHeader.h"

class MCSE 
{
public:
    std::vector<char> fill;
    unsigned int size;

    MCSE(std::fstream& adtFile, unsigned int startByte)
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

    friend std::ostream& operator<< (std::ostream &stream, MCSE& me) 
    {
        ChunkHeader CHeader("MCSE", me.size);
        stream << CHeader;

        if (me.size)
            stream.write(&me.fill[0], me.size);        

        return stream;
    }
};

#endif