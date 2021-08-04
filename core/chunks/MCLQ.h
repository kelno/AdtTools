#ifndef MCLQ_H
#define MCLQ_H

#include "chunkHeader.h"
#include <array>

struct MCNKEntry;

struct MCLQInfo 
{
    union {
        struct SWVert {
            char depth;
            char flow0Pct;
            char flow1Pct;
            char filler;
            float height;
        } waterVert;
        struct SOVert {
            char depth; // signed
            char foam;
            char wet;
            char filler;
        } oceanVert;
        struct SMVert {
            unsigned __int16 s; // can't make sense of those yet, but if they're both 0 the float contains garbage
            unsigned __int16 t;
            float height;
        } magmaVert;
    };
};

unsigned int constexpr VERTEXES_SIDE = 9;
unsigned int constexpr VERTEXES_COUNT = VERTEXES_SIDE * VERTEXES_SIDE;

struct C3Vector
{
    /*0x00*/  float x;
    /*0x04*/  float y;
    /*0x08*/  float z;
};

struct CAaSphere
{
    C3Vector position;
    float radius;
};

struct SWFlowv {
    CAaSphere sphere;
    C3Vector dir;
    float velocity;
    float amplitude;
    float frequency;
}; 

enum MCLQFlags : unsigned char
{
    // something is funky. From what I can see when reading files, this is indeed a uint8 value, but the enum here given by https://wowdev.wiki/ADT/v18#MCLQ_sub-chunk goes above 255

    // 0x0f or 0x8 mean don't render (?, TC: 0xF)
    // &0xf: liquid type (1: ocean, 3: slime, 4: river, 6: magma)
    // 0x10:
    // 0x20:
    // 0x40: not low depth (forced swimming ?)
    // 0x80: fatigue (?, TC: yes)

    FLAG_OCEAN = 1,
    FLAG_SLIME = 3,
    FLAG_RIVER = 4, // confirmed
    FLAG_MAGMA = 6,
    FLAG_DONT_RENDER = 0xF, // confirmed
    FLAG_UNK = 0x40, // seems to appear often
    FLAG_FATIGUE = 0x80, // not confirmed 100% but ocean has it
};

struct MCLQEntry 
{
    float rangeMin;
    float rangeMax;
    std::array<MCLQInfo, VERTEXES_COUNT> info; //cannot find the effect of the first
    std::array<MCLQFlags, 8*8> flags;
    unsigned int nFlowvs; //size of next field? no ideea what this is for if the next commnt is true. 
    std::array<SWFlowv, 2> flowvs; // always 2 in file, independent on nFlowvs. 
    // Format might be different depending on liquid type, I get consistent data for ocean but river and magma are garbage
};

class MCLQ {
public:
    MCLQEntry entry;
    unsigned int size;
    unsigned int sizeLiquid; //total size, cheader included

    MCLQ(std::fstream& adtFile, MCNKEntry const& _mcnk, unsigned int startByte, unsigned int liquidSize);
    MCLQ(MCNKEntry const& _mcnk, float height);

    friend std::ostream& operator<< (std::ostream& stream, MCLQ& me);
private:
    MCNKEntry const& mcnkEntry;
};

#endif
