#ifndef CHARARRAYCHUNK_H
#define CHARARRAYCHUNK_H

#include "chunkHeader.h"
#include <array>

class CharArrayChunk 
{
public:
    unsigned int size;
    std::string fileNames;
    ChunkName chunkName;

    CharArrayChunk(std::string_view name, std::fstream& adtFile, unsigned int startByte);

    friend std::ostream& operator<< (std::ostream& stream, const CharArrayChunk& me);
};


#endif