// zero-terminated strings with complete paths to models. Referenced in MWID.

#ifndef MWMO_H
#define MWMO_H

#include "CharArrayChunk.h"

class MWMO : public CharArrayChunk {
public:
	CharArrayChunk* data;
	MWMO(std::fstream& adtFile, unsigned int startByte) :
		CharArrayChunk("MWMO", adtFile, startByte)
	{}
};

#endif