#ifndef MCLY_H
#define MCLY_H
#include <vector>
#include "chunkHeader.h"

struct Layer // 03-29-2005 By ObscuR, --schlumpf_ 19:47, 19 August 2009 (CEST)
{
/*000h*/  unsigned int textureId; 
/*004h*/  unsigned int flags;		
/*008h*/  unsigned int offsetInMCAL;
/*00Ch*/  unsigned short effectId;
/*00Eh*/  unsigned short padding;
/*010h*/  		
};

class MCLY {
public:
	std::vector<Layer> Layers;
		
	MCLY(std::fstream& adtFile, unsigned int startByte) {
		adtFile.seekg(startByte);
		chunkHeader CHeader(adtFile);
		unsigned int size = CHeader.chunkSize;
		for (unsigned int i = 0; i < (size / sizeof(Layer)); i++) {
			Layer cur;
			adtFile.read(reinterpret_cast<char *>(&cur), sizeof(Layer));
			Layers.push_back(cur);
		}
	}
	friend std::ostream& operator<< (std::ostream &stream, MCLY& me) {
		chunkHeader CHeader("MCLY", unsigned int(me.Layers.size()) * sizeof(Layer));
		stream << CHeader;

		stream.write(reinterpret_cast<char *>(&me.Layers[0]), sizeof(Layer) * me.Layers.size());		

		return stream;
	}
};

#endif