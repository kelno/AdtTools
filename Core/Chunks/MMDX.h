// zero-terminated strings with complete paths to models. Referenced in MMID.
#ifndef MMDX_H
#define MMDX_H

#include "CharArrayChunk.h"

class MMDX : public CharArrayChunk {
public:
	CharArrayChunk* data;
	MMDX(std::fstream& adtFile, unsigned int startByte) :  
		CharArrayChunk("MMDX", adtFile, startByte)
	{}
};

#endif