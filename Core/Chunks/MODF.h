#include "chunkHeader.h"

#ifndef MODF_H
#define MODF_H

/*
enum MODFFlags {
    modf_destroyable = 1,         // set for destroyable buildings like the tower in DeathknightStart. This makes it a server-controllable game object.
  };
*/
struct MODFEntry {
    unsigned int mwidEntry;           // references an entry in the MWID chunk, specifying the model to use.
    unsigned int uniqueId;            // this ID should be unique for all ADTs currently loaded. Best, they are unique for the whole map.
    float position[3];
    float rotation[3];            // same as in MDDF.
    float lowerBounds[3];         // these two are position plus the wmo bounding box.
    float upperBounds[3];         // they are used for defining when if they are rendered as well as collision.
    unsigned short flags;               // values from enum MODFFlags.
    unsigned short doodadSet;           // which WMO doodad set is used.
    unsigned short nameSet;             // which WMO name set is used. Used for renaming goldshire inn to northshire inn while using the same model.
    unsigned short padding;             // it reads only a WORD into the WMAPOBJDEF structure for name. I don't know about the rest.
};

class MODF {
public:
  unsigned int size;
  MODFEntry* entries;

  MODF(std::fstream& adtFile, unsigned int startByte) {  
		adtFile.seekg(startByte);
		chunkHeader MODFHeader(adtFile);
		size = MODFHeader.chunkSize;
		entries = (MODFEntry*)new char[size];
		adtFile.read(reinterpret_cast<char *>(entries), size);
  }
  friend std::ostream& operator<< (std::ostream &stream, MODF& me){
		chunkHeader CHeader("MODF",me.size);
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(me.entries),me.size);

		return stream;
	}
};

#endif