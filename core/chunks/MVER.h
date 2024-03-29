#ifndef MVER_H
#define MVER_H

#include "chunkHeader.h"
#include "logger.h"

unsigned int constexpr MVER_SIZE = sizeof(int);

class MVER 
{
public:
    unsigned int version;

    //can throw
    MVER(std::fstream& adtFile)
    { 
        adtFile.seekg(std::ios::beg);
        ChunkHeader MVER_CHeader(adtFile);
        MVER_CHeader.CheckTitle("MVER");

        adtFile.read(reinterpret_cast<char*>(&version), MVER_SIZE);
    }

    MVER(unsigned int version) :
        version(version)
    { }

    friend std::ostream& operator<< (std::ostream &stream, MVER& me)
    {
        ChunkHeader CHeader("MVER", 4);
        stream << CHeader;
        stream.write(reinterpret_cast<char *>(&me.version), MVER_SIZE);

        return stream;
    }
};

#endif