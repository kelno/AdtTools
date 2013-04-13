//by Kelno
#include "adt.h"
#include <iostream>

using namespace std;
//using std::ios;

fstream adtFile;

int main(int argc, char **argv) {
	if(argc == 1)
		cout << "Fix MFBO (bounding box for flying) bug from Noggit for given adts.\nUsage : FixMFBO <adt files>...\n";
	
	for(int i = 1; i < argc; i++) {
		adtFile.open(argv[i], ios::in | ios::out | ios::binary);
		adt ADT(adtFile);
		if (ADT.mfbo->isBroken())
			ADT.mfbo->invert();

		ADT.writeToDisk(adtFile);
		adtFile.close();
	} 
}
