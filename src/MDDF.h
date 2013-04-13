#include "chunkHeader.h"

#ifndef MDDF_H
#define MDDF_H

/*
enum MDDFFlags {
mddf_biodome = 1,             // this sets internal flags to | 0x800 (WDOODADDEF.var0xC).
mddf_shrubbery = 2,           // the actual meaning of these is unknown to me. maybe biodome is for really big M2s.
}; */

struct MDDFEntry {
    unsigned int mmidEntry;           // references an entry in the MMID chunk, specifying the model to use.
    unsigned int uniqueId;            // this ID should be unique for all ADTs currently loaded. Best, they are unique for the whole map. Blizzard has these unique for the whole game.
    float position[3];
    float rotation[3];            // degrees. This is not the same coordinate system orientation like the ADT itself! (see history.)
    unsigned short scale;               // 1024 is the default size equaling 1.0f.
    unsigned short flags;               // values from enum MDDFFlags.
};

class MDDF {
public:
	unsigned int size;
    MDDFEntry* entries;

	MDDF(std::fstream& adtFile, unsigned int startByte) {  
		adtFile.seekg(startByte);
		chunkHeader MDDFHeader(adtFile);
		size = MDDFHeader.chunkSize;
		entries = (MDDFEntry*)new char[size];
		adtFile.read(reinterpret_cast<char *>(entries), size);
    }
	friend std::ostream& operator<< (std::ostream &stream, MDDF& me){
		chunkHeader CHeader("MDDF",me.size);
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(me.entries),me.size);

		return stream;
	}
};

#endif