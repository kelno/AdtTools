#ifndef MFBO_H
#define MFBO_H

#include "chunkHeader.h"
#include <array>

struct plane 
{
    std::array<std::array<short, 3>, 3> height;
};

class MFBO 
{
public:
    MFBO(std::fstream& adtFile, unsigned int startByte);

    void Set(short min, short max);
    const short GetMin();
    const short GetMax();
    bool HasInvertedMinMax();
    void InvertMinMax();

    friend std::ostream& operator<< (std::ostream &stream, MFBO& me) 
    {
        ChunkHeader CHeader("MFBO",sizeof(plane)*2);
        stream << CHeader;
        stream.write(reinterpret_cast<char *>(&me.maximum),sizeof(plane));
        stream.write(reinterpret_cast<char *>(&me.minimum),sizeof(plane));
        return stream;
    };
private:
    plane maximum;
    plane minimum;
};

#endif