// zero-terminated strings with complete paths to textures. Referenced in MCLY.
#ifndef MTEX_H
#define MTEX_H

#include "CharArrayChunk.h"
#include "debuglog.h"

class MTEX : public CharArrayChunk {
public:
	//CharArrayChunk* data;
	MTEX(std::fstream& adtFile, unsigned int startByte, DebugLog* debug_log) :
	  CharArrayChunk("MTEX", adtFile, startByte, debug_log)
	  {}
};

#endif