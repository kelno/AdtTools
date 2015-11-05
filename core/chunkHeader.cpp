#include "chunkHeader.h"

chunkHeader::chunkHeader(char* str, unsigned int size) :
		chunkSize(size) {
		title[0] = str[3];
		title[1] = str[2];
		title[2] = str[1];
		title[3] = str[0];
}
chunkHeader::chunkHeader(std::fstream& adtFile){
	adtFile.read(reinterpret_cast<char *>(title), sizeof(chunkHeader));
}

std::ostream& operator<< (std::ostream &stream, chunkHeader& me) {
	stream.write(me.title, sizeof(chunkHeader));
	return stream;
}

char* chunkHeader::invertTitle(char* title) {  //pour une output
	char* newTitle = new char[4];
	newTitle[0] = title[3];
	newTitle[1] = title[2];
	newTitle[2] = title[1];
	newTitle[3] = title[0];
	return newTitle;
}