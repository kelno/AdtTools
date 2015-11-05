// filename starting position in MMDX chunk. These entries are getting referenced in the MDDF chunk.

#ifndef MMID_H
#define MMID_H

#include "IntArrayChunk.h"

class MMID {
public:
	IntArrayChunk* data;
  MMID(std::fstream& adtFile, unsigned int startByte) { //comment utiliser constructeur au dessus?
	  data = new IntArrayChunk(adtFile, startByte);
  }
  friend std::ostream& operator<< (std::ostream &stream, MMID& me){
		chunkHeader CHeader("MMID",me.data->size);
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(me.data->offsets),me.data->size);

		return stream;
	}
};

#endif