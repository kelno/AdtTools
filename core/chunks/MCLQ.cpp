#include "MCLQ.h"
#include "MCNK.h"

MCLQ::MCLQ(std::fstream& adtFile, MCNKEntry const& _mcnk, unsigned int startByte, unsigned int liquidSize) :
    sizeLiquid(liquidSize),
    mcnkEntry(_mcnk)
{
    adtFile.seekg(startByte);
    ChunkHeader CHeader(adtFile);
    size = CHeader.chunkSize;
    //fill = new char[size + sizeLiquid - sizeof(ChunkHeader)];
    //adtFile.read(fill, size + sizeLiquid - sizeof(ChunkHeader));
    adtFile.read(reinterpret_cast<char *>(&entry), size + sizeLiquid - sizeof(ChunkHeader));
    //if ((mcnkEntry.header.flags & 0xF) == FLAG_LQ_RIVER)
    //{
    //    int a = 0;
    //}
    //if ((mcnkEntry.header.flags & 0xF) == FLAG_LQ_OCEAN)
    //{
    //    int a = 0;
    //}
    //if (   ((mcnkEntry.header.flags & 0xF) == FLAG_LQ_MAGMA)
    //    || ((mcnkEntry.header.flags & 0xF) == FLAG_SLIME)    ) // not sure it's using the same but guessed
    //{
    //    int a = 0;
    //}
}

MCLQ::MCLQ(MCNKEntry const& _mcnk, float height) :
    mcnkEntry(_mcnk)
{
    size = 0; // not sure what to put here
    sizeLiquid = sizeof(MCLQEntry) + sizeof(ChunkHeader);
    {
        // for now, start with 0 everywhere for MCLQEntry
        memset(&entry, 0, sizeof(entry));
        entry.rangeMin = 0.0f;
        entry.rangeMax = 0.0f;

        if ((mcnkEntry.header.flags & 0xF) == FLAG_LQ_RIVER) {
            for (unsigned int i = 0; i < entry.info.size(); ++i)
                entry.info[i].waterVert.height = height;
            for (unsigned int i = 0; i < entry.flags.size(); ++i)
                entry.flags[i] = FLAG_RIVER;
        }
        else if ((mcnkEntry.header.flags & 0xF) == FLAG_LQ_OCEAN) {
            // can't change height for this type
            for (unsigned int i = 0; i < entry.info.size(); ++i)
                entry.info[i].oceanVert.depth = -1;
            for (unsigned int i = 0; i < entry.flags.size(); ++i)
                entry.flags[i] = FLAG_OCEAN;
        }
        else if (((mcnkEntry.header.flags & 0xF) == FLAG_LQ_MAGMA)
             || ((mcnkEntry.header.flags & 0xF) == FLAG_SLIME)) { // not sure it's using the same but guessed
            for (unsigned int i = 0; i < entry.info.size(); ++i)
            {
                //doesn't work yet, can't figure what s and t mean
                entry.info[i].magmaVert.s = 256;
                entry.info[i].magmaVert.t = 64;
                entry.info[i].magmaVert.height = height;
            }
            for (unsigned int i = 0; i < entry.flags.size(); ++i)
                entry.flags[i] = FLAG_MAGMA;
        }
    }
}

std::ostream& operator<<(std::ostream& stream, MCLQ& me)
{
    ChunkHeader CHeader("MCLQ", me.size);
    stream << CHeader;

    stream.write(reinterpret_cast<char*>(&me.entry), me.sizeLiquid - sizeof(ChunkHeader));

    return stream;
}
