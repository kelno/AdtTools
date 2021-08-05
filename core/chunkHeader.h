#ifndef CHUNKHEADER_H
#define CHUNKHEADER_H

#include <fstream>
#include <iomanip>
#include <iostream>

/*
ChunkHeader
    000h char[4] titre
    004h uint32 chunkSize
    008h -
*/

unsigned int constexpr CHUNKHEADER_SIZE = 8;
unsigned int constexpr CHUNKS_PER_SIDE = 16;
unsigned int constexpr CHUNKS_PER_ADT = CHUNKS_PER_SIDE * CHUNKS_PER_SIDE;

class ChunkHeader 
{
public:
    char title[4];
    unsigned int chunkSize;

    //given parameters
    ChunkHeader(char* str, unsigned int size);
    //raw from file
    ChunkHeader(std::fstream& adtFile);

    friend std::ostream& operator<< (std::ostream &stream, ChunkHeader& me);

    char* InvertTitle(char* title);
};

#endif
;