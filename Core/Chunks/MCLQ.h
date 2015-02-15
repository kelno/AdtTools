#ifndef MCLQ_H
#define MCLQ_H

#include "chunkHeader.h"
#include <random>

struct MCLQInfo {
	float dunno;//most time at 0. Something about inclinaison? Another target height?
	float height;
};

//this one may be completely wrong, complete guess by myself (kelno). Seems wrong but okay for allwater
struct MCLQEntry {
	MCLQInfo info[1+9*9]; //cannot find the effect of the first
	char flags1[8*8]; //not render = 0x0F. Commonly 0x04 
	char flags2[1+9*9];  //Set to 0xFF? Je vois pas la différence quoi que je mette
	unsigned short unused; //or not?
};
//total = 656 + 64 + 82 + 2 = 804 OK (add cheader to reach 812 = sizeLiquid)


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

	MCLQ(float height, float dunno, char flags1 = (char)0x04, char flags2 = (char)0xFF)
    {
		sizeLiquid = sizeof(MCLQEntry) + sizeof(chunkHeader);
		for (int i = 0; i < 9*9+1; i++) {
			entry.info[i].dunno = dunno;
			entry.info[i].height = height;

			entry.flags2[i] = flags2;
		}
		for (int i = 0; i < 8*8; i++) {
			entry.flags1[i] = flags1;
		}
		entry.unused = 0;
	}

	friend std::ostream& operator<< (std::ostream &stream, MCLQ& me) 
    {
		chunkHeader CHeader("MCLQ", me.size);
		stream << CHeader;

		//stream.write(me.fill, me.size + me.sizeLiquid - sizeof(chunkHeader));	
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


