#ifndef MCRF_H
#define MCRF_H

#include "chunkHeader.h"

class MCRF 
{
public:
    std::vector<char> fill;
    unsigned int size;

    MCRF(std::fstream& adtFile, unsigned int startByte)
    {
        //std::cout << "startbyte " << std::hex << startByte << std::endl;
        adtFile.seekg(startByte);
        ChunkHeader CHeader(adtFile);
        size = CHeader.chunkSize;
        //std::cout << "size " << std::hex << size << std::endl;
        if (size)
        {
            fill.resize(size);
            adtFile.read(&fill[0], size);
        }
    }

    friend std::ostream& operator<< (std::ostream &stream, MCRF& me) 
    {
        ChunkHeader CHeader("MCRF", me.size);
        stream << CHeader;

        if (me.size)
            stream.write(&me.fill[0], me.size);        

        return stream;
    }
};

#endif