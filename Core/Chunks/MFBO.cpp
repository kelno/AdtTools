#include "MFBO.h"

MFBO::MFBO() {};
MFBO::MFBO(std::fstream& adtFile, unsigned int startByte) {  
	adtFile.seekg(startByte);
	adtFile.seekg(sizeof(chunkHeader), std::ios_base::cur);
	adtFile.read(reinterpret_cast<char *>(&maximum), sizeof(MFBO));
}
void MFBO::set(short min, short max)
{
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			maximum.height[i][j] = max;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			minimum.height[i][j] = min;
};
const short MFBO::getMin()
{
	return minimum.height[0][0];
};

const short MFBO::getMax()
{
	return maximum.height[0][0];
};

bool MFBO::hasInvertedMinMax()
{
	if(maximum.height[0][0] < minimum.height[0][0])
		return true;
	else
		return false;
};

void MFBO::invertMinMax() 
{
	set(getMax(),getMin());
};