#ifndef MCAL_H
#define MCAL_H

#include "chunkHeader.h"

class MCAL 
{
public:
    std::vector<char> fill;
    unsigned int size;

    MCAL(std::fstream& adtFile, unsigned int startByte) 
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

    friend std::ostream& operator<< (std::ostream &stream, MCAL& me) 
    {
        ChunkHeader CHeader("MCAL", me.size);
        stream << CHeader;

        if (me.size)
            stream.write(&me.fill[0], me.size);        

        return stream;
    }
};

#endif