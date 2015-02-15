#ifndef MFBO_H
#define MFBO_H

#include "chunkHeader.h"

struct plane {
    short height[3][3];
};

class MFBO {
public:
	MFBO();
    void set(short min, short max);
    const short getMin();
    const short getMax();
	bool hasInvertedMinMax();
	void invertMinMax();

	MFBO(std::fstream& adtFile, unsigned int startByte);
	friend std::ostream& operator<< (std::ostream &stream, MFBO& me){
		chunkHeader CHeader("MFBO",sizeof(plane)*2);
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(&me.maximum),sizeof(plane));
		stream.write(reinterpret_cast<char *>(&me.minimum),sizeof(plane));
		return stream;
	};
private:
    plane maximum;
    plane minimum;
};

#endif