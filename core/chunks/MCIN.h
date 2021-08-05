#ifndef MCIN_H
#define MCIN_H

#include "ChunkHeader.h"

struct MCINEntry
{
    unsigned int mcnkOffs;            // absolute offset.
    unsigned int size;                // the size of the MCNK chunk, this is refering to. (including cheader)
    unsigned int flags;               // these two are always 0. only set in the client.
    unsigned int asyncId;
};

// Pointers to MCNK chunks and their sizes.
class MCIN 
{
public:
    MCINEntry entries[CHUNKS_PER_ADT];

    MCIN(std::fstream& adtFile, unsigned int startByte) 
    {
        adtFile.seekg(startByte);
        ChunkHeader CHeader(adtFile);
        CHeader.CheckTitle("MCIN");

        adtFile.read(reinterpret_cast<char*>(entries), sizeof(MCINEntry) * CHUNKS_PER_ADT);
    }

    unsigned int getMCNKSize() 
    {
        unsigned int sum = 0;
        for (unsigned int i = 0; i < CHUNKS_PER_ADT; ++i) {
            sum += entries[i].size;
        }
        return sum;
    }

    friend std::ostream& operator<< (std::ostream& stream, MCIN& me) 
    {
        ChunkHeader CHeader("MCIN", sizeof(MCINEntry) * CHUNKS_PER_ADT);
        stream << CHeader;
        stream.write(reinterpret_cast<char*>(&me.entries), sizeof(MCINEntry) * CHUNKS_PER_ADT);

        return stream;
    }
};

#endif