#include "MFBO.h"

MFBO::MFBO(std::fstream& adtFile, unsigned int startByte) 
{  
    adtFile.seekg(startByte);
    adtFile.seekg(sizeof(ChunkHeader), std::ios_base::cur);
    adtFile.read(reinterpret_cast<char *>(&maximum), sizeof(MFBO));
}

void MFBO::Set(short _min, short _max)
{
    for (auto& itr : maximum.height)
        for (auto& max : itr)
            max = _max;

    for (auto& itr : minimum.height)
        for (auto& min : itr)
            min = _min;
};

const short MFBO::GetMin()
{
    return minimum.height[0][0];
};

const short MFBO::GetMax()
{
    return maximum.height[0][0];
};

bool MFBO::HasInvertedMinMax()
{
    if (maximum.height[0][0] < minimum.height[0][0])
        return true;
    else
        return false;
};

void MFBO::InvertMinMax() 
{
    Set(GetMax(), GetMin());
};