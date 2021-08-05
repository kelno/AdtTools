#include "chunkHeader.h"

#ifndef MDDF_H
#define MDDF_H

/*
enum MDDFFlags 
{
mddf_biodome = 1,             // this sets internal flags to | 0x800 (WDOODADDEF.var0xC).
mddf_shrubbery = 2,           // the actual meaning of these is unknown to me. maybe biodome is for really big M2s.
}; */

struct MDDFEntry 
{
    unsigned int mmidEntry;           // references an entry in the MMID chunk, specifying the model to use.
    unsigned int uniqueId;            // this ID should be unique for all ADTs currently loaded. Best, they are unique for the whole map. Blizzard has these unique for the whole game.
    float position[3];
    float rotation[3];                // degrees. This is not the same coordinate system orientation like the ADT itself! (see history.)
    unsigned short scale;             // 1024 is the default size equaling 1.0f.
    unsigned short flags;             // values from enum MDDFFlags.
};

class MDDF 
{
public:
    unsigned int size;
    std::vector<MDDFEntry> entries;

    MDDF(std::fstream& adtFile, unsigned int startByte) 
    {
        adtFile.seekg(startByte);
        ChunkHeader MDDFHeader(adtFile);
        size = MDDFHeader.chunkSize;
        unsigned int mddfCount = size / sizeof(MDDFEntry);
        if (size % sizeof(MDDFEntry) != 0)
        {
            sLogger->Out(Logger::LOG_LEVEL_ERROR, "MDDF has a size that's not a multiple of sizeof(MDDFEntry), skipping remaining bytes");
            size = mddfCount * sizeof(MDDFEntry);
        }

        entries.resize(mddfCount);
        for (unsigned int i = 0; i < mddfCount; ++i)
            adtFile.read(reinterpret_cast<char*>(&entries[i]), sizeof(MDDFEntry));
    }

    friend std::ostream& operator<< (std::ostream& stream, MDDF& me)
    {
        ChunkHeader CHeader("MDDF", me.size);
        stream << CHeader;
        stream.write(reinterpret_cast<char *>(&me.entries[0]), me.size);

        return stream;
    }
};

#endif