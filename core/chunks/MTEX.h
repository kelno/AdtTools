// zero-terminated strings with complete paths to textures. Referenced in MCLY.
#ifndef MTEX_H
#define MTEX_H

#include "CharArrayChunk.h"

class MTEX : public CharArrayChunk {
public:
	//CharArrayChunk* data;
	MTEX(std::fstream& adtFile, unsigned int startByte) :
	  CharArrayChunk("MTEX", adtFile, startByte)
	  {}
};

#endif