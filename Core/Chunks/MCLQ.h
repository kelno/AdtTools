#ifndef MCLQ_H
#define MCLQ_H

#include "chunkHeader.h"
#include <random>

struct MCLQInfo 
{
	float dunno;//most time at 0. Something about inclinaison? Another target height?
	float height;
};

//this one may be completely wrong, complete guess by myself (kelno). Seems wrong but okay for allwater
struct MCLQEntry 
{
	MCLQInfo info[1+9*9]; //cannot find the effect of the first
	char flags1[8*8]; //not render = 0x0F. Commonly 0x04 
	char flags2[1+9*9];  //Set to 0xFF? Don't see any difference whatever I try
	unsigned short unused; //or not?
};
//total = 656 + 64 + 82 + 2 = 804 OK (add cheader to reach 812 = sizeLiquid)

enum MCLQ_Flags1
{
    MCLQ_FLAG1_NONE  = 0x00,
    MCLQ_FLAG1_UNK_1 = 0x01,
    MCLQ_FLAG1_UNK_2 = 0x02,
    MCLQ_FLAG1_UNK_3 = 0x04, //common value, no idea what does it do
    MCLQ_FLAG1_NO_RENDER = 0x0F,
};

//Binary flag for 256 sub parts ?
enum MCLQ_Flags2
{
    MCLQ_FLAG2_NONE = 0x00,
    MCLQ_FLAG2_ALL  = 0xFF,
};

class MCLQ {
public:
	MCLQEntry entry;
	unsigned int size;
	unsigned int sizeLiquid; //total size, cheader included

	MCLQ(std::fstream& adtFile, unsigned int startByte, unsigned int liquidSize)
    {
		sizeLiquid = liquidSize;

		adtFile.seekg(startByte);
		chunkHeader CHeader(adtFile);
		size = CHeader.chunkSize;
		//fill = new char[size + sizeLiquid - sizeof(chunkHeader)];
		//adtFile.read(fill, size + sizeLiquid - sizeof(chunkHeader));
		adtFile.read(reinterpret_cast<char *>(&entry), size + sizeLiquid - sizeof(chunkHeader));
	}

	MCLQ(float height, float dunno, MCLQ_Flags1 flags1 = MCLQ_FLAG1_UNK_3, MCLQ_Flags2 flags2 = MCLQ_FLAG2_ALL)
    {
		sizeLiquid = sizeof(MCLQEntry) + sizeof(chunkHeader);
		for (int i = 0; i < 9*9+1; i++) {
			entry.info[i].dunno = dunno;
			entry.info[i].height = height;

			entry.flags2[i] = char(flags2);
		}
		for (int i = 0; i < 8*8; i++) {
			entry.flags1[i] = char(flags1);
		}
		entry.unused = 0;
	}

	friend std::ostream& operator<< (std::ostream &stream, MCLQ& me) 
    {
		chunkHeader CHeader("MCLQ", me.size);
		stream << CHeader;

		stream.write(reinterpret_cast<char *>(&me.entry), me.sizeLiquid - sizeof(chunkHeader));

		return stream;
	}
};

#endif

/*
flags1
0x00 affiche rien
0x01 affiche rien
0x02 affiche rien
0x04 affiche normalement
0x05 affiche rien
j'abandooonne
0x44 affiche (32 + 8 + 4)
*/


