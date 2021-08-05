#ifndef CHUNKHEADER_H
#define CHUNKHEADER_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <array>
#include <string_view>

/*
ChunkHeader
    000h char[4] titre
    004h uint32 chunkSize
    008h -
*/

unsigned int constexpr CHUNKHEADER_SIZE = 8;
unsigned int constexpr CHUNKS_PER_SIDE = 16;
unsigned int constexpr CHUNKS_PER_ADT = CHUNKS_PER_SIDE * CHUNKS_PER_SIDE;

unsigned int constexpr CHUNK_NAME_SIZE = 4;
using ChunkName = std::array<char, CHUNK_NAME_SIZE>;

class ChunkHeader 
{
public:
    ChunkName title; // title is stored in reverse
    unsigned int chunkSize;

    ChunkHeader(std::string_view str, unsigned int size);
    ChunkHeader(ChunkName title, unsigned int size);
    //raw from file
    ChunkHeader(std::fstream& adtFile);

    // throws if titles do not match
    void CheckTitle(std::string_view checkTitle) const;

    friend std::ostream& operator<< (std::ostream &stream, ChunkHeader& me);
};

#endif
;