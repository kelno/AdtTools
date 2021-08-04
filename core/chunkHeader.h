#ifndef CHUNKHEADER_H
#define CHUNKHEADER_H

#include <fstream>
#include <iomanip>
#include <iostream>

/*
chunkHeader
    000h char[4] titre
    004h uint32 chunkSize
    008h -
*/

unsigned int constexpr CHUNKHEADER_SIZE = 8;
unsigned int constexpr CHUNKS_PER_SIDE = 16;
unsigned int constexpr CHUNKS_PER_ADT = CHUNKS_PER_SIDE * CHUNKS_PER_SIDE;

class chunkHeader {
public:
    char title[4];
    unsigned int chunkSize;

    //given parameters
    chunkHeader(char* str, unsigned int size);
    //raw from file
    chunkHeader(std::fstream& adtFile);

    friend std::ostream& operator<< (std::ostream &stream, chunkHeader& me);

    char* invertTitle(char* title);
};

#endif
;