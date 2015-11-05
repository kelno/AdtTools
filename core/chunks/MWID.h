// filename starting position in MWMO chunk. These entries are getting referenced in the MODF chunk.
#ifndef MWID_H
#define MWID_H

#include "IntArrayChunk.h"

class MWID  {
public:
	IntArrayChunk* data;
	MWID(std::fstream& adtFile, unsigned int startByte) { 
		data = new IntArrayChunk(adtFile, startByte);
	}
	friend std::ostream& operator<< (std::ostream &stream, MWID& me){
		chunkHeader CHeader("MWID",me.data->size);
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(me.data->offsets),me.data->size);

		return stream;
	}
};

#endif