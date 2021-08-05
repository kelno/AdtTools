#ifndef MCAL_H
#define MCAL_H

#include "chunkHeader.h"

class MCAL 
{
public:
    char* fill;
    unsigned int size;

    MCAL(std::fstream& adtFile, unsigned int startByte) 
    {
        adtFile.seekg(startByte);
        ChunkHeader CHeader(adtFile);
        size = CHeader.chunkSize;
        fill = new char[size];
        adtFile.read(fill, size);
    }

    friend std::ostream& operator<< (std::ostream &stream, MCAL& me) 
    {
        ChunkHeader CHeader("MCAL", me.size);
        stream << CHeader;

        stream.write(me.fill, me.size);        

        return stream;
    }
};

#endif