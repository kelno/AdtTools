#ifndef MH2O_H
#define MH2O_H

#include "chunkHeader.h"
#include <vector>

struct MH2O_Header
{
/*0x000*/ unsigned int ofsInformation;			//An offset to the MH2O_Information struct(s) for this chunk.
/*0x004*/ unsigned int layerCount;			    //0 if the chunk has no liquids. If > 1, the offsets will point to arrays.
/*0x008*/ unsigned int ofsRender;				//An offset to the 64 bit render mask.
/*0x012*/
};

struct MH2O_Information
{
/*0x000*/	unsigned short liquidTypeId;			//Points to LiquidType.dbc
/*0x002*/	unsigned short flags;                  
/*0x004*/	float minHeightLevel;                   // as used in bounding radius calculations //The global liquid-height of this chunk. Which is always in there twice. Blizzard knows why
/*0x008*/	float maxHeightLevel;
/*0x00C*/	char xOffset;				//The X offset of the liquid square (0-7)
/*0x00D*/	char yOffset;				//The Y offset of the liquid square (0-7)
/*0x00E*/	char width;					//The width of the liquid square (1-8)
/*0x00F*/	char height;				 //The height of the liquid square (1-8)
/*0x010*/	unsigned int Mask2;				// points to an array of bits with information about the mask. w*h bits (=h bytes). If Mask2 == 0 and Render == 0, then there is no HeightMapData
/*0x014*/	unsigned int HeightmapData;	//Offset to MH2O_HeightmapData structure for this chunk.
/*0x018*/
};

struct MH2O_HeightmapData
{
	// if type & 1 != 1, this chunk is "ocean".  in this case, do not use this structure.

	float* heightMap; 	// w*h
	char* transparency; 	// w*h
};
//BWAAAH. Refaire des classes, trop compliqué, trop d'inconnues.
class MH2O {
public:
	unsigned int size;
	/*MH2O_Header Header[16*16];
	std::vector<MH2O_Information> Info;
	std::vector<double> RenderMasks;
	std::vector<double> RenderMasks2;
	std::vector<MH2O_HeightmapData> HeightmapData; */
    char* fill;
	unsigned int remainingBytes;

	MH2O(std::fstream& adtFile, unsigned int startByte) {  
		adtFile.seekg(startByte);
		chunkHeader MH2OHeader(adtFile);
		size = MH2OHeader.chunkSize;
		/*
		//le bloc Info a obligé une taille fixe nan? Dans le doute
		unsigned int start = (unsigned int)adtFile.tellp();
		for (int i = 0; i < 256; i++) 
		{
			adtFile.seekp(start + i * sizeof(Header));
			adtFile.read(reinterpret_cast<char *>(&Header[i]), sizeof(MH2O_Header));
			if(Header[i].ofsInformation != 0)
			{
				adtFile.seekp(start + Header[i].ofsInformation);
				MH2O_Information curInfo;
				adtFile.read(reinterpret_cast<char *>(&curInfo), sizeof(MH2O_Information));
				Info.push_back(curInfo);
				if (curInfo.Mask2 != 0)
				{
					adtFile.seekp(start + curInfo.Mask2);
					double curMask;
					adtFile.read(reinterpret_cast<char *>(&curMask), sizeof(double));
					RenderMasks2.push_back(curMask);
				}
			}
			if(Header[i].ofsRender != 0)
			{
				adtFile.seekp(start + Header[i].ofsRender);
				double curMask;
				adtFile.read(reinterpret_cast<char *>(&curMask), sizeof(double));
				RenderMasks.push_back(curMask);
			}
		}
		
		std::cout << std::hex << "MH2O_Headers size : " << sizeof(Header) << std::endl;
		std::cout << std::hex << "MH2O_Information size : " << Info.size() * sizeof(MH2O_Information) << std::endl;
		std::cout << std::hex << "MH2O_RenderMasks size : " << RenderMasks.size() * sizeof(double) << std::endl;
		*/
		//std::cout << std::hex << "MH2O size " << size << std::endl;

		//HACK
		adtFile.seekg(0, std::ifstream::end);
		remainingBytes = (unsigned int)adtFile.tellg() - (startByte + sizeof(chunkHeader)) - size;
		//std::cout << std::hex << "MH2O rem " << remainingBytes << std::endl;
		size += remainingBytes;
		fill = new char[size];
		adtFile.seekg(startByte + sizeof(chunkHeader));
		adtFile.read(fill, size);
    }
	friend std::ostream& operator<< (std::ostream &stream, MH2O& me){
		chunkHeader CHeader("MH2O",me.size - me.remainingBytes);
		stream << CHeader;
		stream.write(me.fill,me.size);
		/*std::cout << "im at " << std::hex << stream.tellp() << std::endl;
		std::cout << "sinon c'etait " << std::hex << (int)stream.tellp() - 82052 << std::endl;*/

		return stream;
	}
};

#endif