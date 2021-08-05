#ifndef INTARRAYCHUNK_H
#define INTARRAYCHUNK_H

#include "chunkHeader.h"

class IntArrayChunk 
{
public:
    unsigned int size;
    std::vector<unsigned int> integers;

    IntArrayChunk(std::fstream& adtFile, unsigned int startByte) {  
        adtFile.seekg(startByte);
        ChunkHeader CHeader(adtFile);
        size = CHeader.chunkSize;

        unsigned int intCount = size / sizeof(unsigned int);
        if (size % sizeof(unsigned int) != 0)
        {
            sLogger->Out(Logger::LOG_LEVEL_ERROR, "IntArrayChunk has a size that's not a multiple of sizeof(unsigned int), skipping remaining bytes");
            size = intCount * sizeof(unsigned int);
        }

        integers.resize(intCount);
        adtFile.read(reinterpret_cast<char*>(&integers[0]), sizeof(unsigned int) * intCount);
    };

    friend std::ostream& operator<< (std::ostream& stream, IntArrayChunk& me)
    {
        stream.write(reinterpret_cast<char*>(&me.integers[0]), me.size);

        return stream;
    }

};

#endif