#include "adt.h"
#include "logger.h"

#define MHDR_OFFSET (2*sizeof(chunkHeader) + MVER_SIZE)
using namespace std;

adt::adt(fstream& adtFile)
{
    //copy the file in buffedAdtFile
    {
        //reserve size
        adtFile.seekg(0, std::ios::end);
        std::streamsize size = adtFile.tellg();
        buffedAdtFile = std::vector<char>(size);

        //read
        adtFile.seekg(0, std::ios::beg);
        if(!adtFile.read(buffedAdtFile.data(), size))
        {
            sLogger->OutMessage(Logger::LOG_LEVEL_ERROR, "Could not get adt file in memory, aborting.");
            exit(1);
        }
    }
    sLogger->OutMessage(Logger::LOG_LEVEL_NORMAL, "Extracting adt data");
    //reset read position at file start
	adtFile.seekg(0, std::ios_base::beg); 
	try {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mver...");
		mver = new MVER(adtFile);
	} catch (char* e) {
        sLogger->OutMessage(Logger::LOG_LEVEL_ERROR, "Exception when constructing MVER : %s", e);
		sLogger->OutMessage(Logger::LOG_LEVEL_ERROR, "Is this an adt file? Aborting...");
		exit(1);
	}
	try {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mhdr...");
		mhdr = new MHDR(adtFile, MHDR_OFFSET - sizeof(chunkHeader));
	} catch (char* e) {
        sLogger->OutMessage(Logger::LOG_LEVEL_ERROR, "Exception when constructing MHDR : %s", e);
        sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Read position %xh", (int)adtFile.tellg());
		sLogger->OutMessage(Logger::LOG_LEVEL_ERROR, "Cannot continue, aborting...");
		exit(1);
	}

	//lesquels peuvent etre vides? Check des chunks perdus dans le vide
	if (mhdr->offsMCIN) {
		try {
			sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mcin...");
			if (mhdr->offsMCIN) 
                mcin = new MCIN(adtFile, MHDR_OFFSET + mhdr->offsMCIN);
		} catch (char* e) {
            sLogger->OutMessage(Logger::LOG_LEVEL_ERROR, "Exception when constructing MCIN : %s", e);
		}
	}
	if (mhdr->offsMTEX) {
		try {
			sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mtex...");
			mtex = new MTEX(adtFile, MHDR_OFFSET + mhdr->offsMTEX);
			//std::cout << mtex->debug_log << endl;
		} catch (char* e) {
            sLogger->OutMessage(Logger::LOG_LEVEL_ERROR, "Exception when constructing MTEX : %s", e);
		}
	}  else
		mtex = nullptr;

	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mmdx...");
	if (mhdr->offsMMDX) mmdx = new MMDX(adtFile, MHDR_OFFSET + mhdr->offsMMDX);
	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mmid...");
	if (mhdr->offsMMID) mmid = new MMID(adtFile, MHDR_OFFSET + mhdr->offsMMID);
	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mwmo...");
	if (mhdr->offsMWMO) mwmo = new MWMO(adtFile, MHDR_OFFSET + mhdr->offsMWMO);
	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mwid...");
	if (mhdr->offsMWID) mwid = new MWID(adtFile, MHDR_OFFSET + mhdr->offsMWID);
	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mddf...");
	if (mhdr->offsMDDF) mddf = new MDDF(adtFile, MHDR_OFFSET + mhdr->offsMDDF);
	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting modf...");
	if (mhdr->offsMODF) modf = new MODF(adtFile, MHDR_OFFSET + mhdr->offsMODF);

	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mcnk...");
	mcnk = new MCNK(adtFile, mcin);

	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mfbo...");
	if (mhdr->offsMFBO)	mfbo = new MFBO(adtFile, MHDR_OFFSET + mhdr->offsMFBO);
	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mh2o...");
	if (mhdr->offsMH2O)	mh2o = new MH2O(adtFile, MHDR_OFFSET + mhdr->offsMH2O);
	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Extracting mtxf...");
	if (mhdr->offsMTXF)	mtxf = new MTXF(adtFile, MHDR_OFFSET + mhdr->offsMTXF);
	sLogger->OutMessage(Logger::LOG_LEVEL_NORMAL, "Extracting done");

	//TODO ValidityCheck
}

adt::~adt()
{
    //todo, free memory
}

void adt::WriteToDisk(fstream& adtFile)
{
	sLogger->OutMessage(Logger::LOG_LEVEL_NORMAL, "Writing adt data");
	adtFile.seekp(0, std::ios_base::beg); 
	adtFile << (*mver);
	adtFile.seekp(sizeof(MHDR) + sizeof(chunkHeader), std::ios_base::cur); //reserving, mhdr written at the end

	mhdr->offsMCIN = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
	adtFile.seekp(sizeof(MCIN) + sizeof(chunkHeader), std::ios_base::cur); //reserving, mcin written at the end
	
	if(mtex) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mtex...");
		mhdr->offsMTEX = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		//std::cout << mtex->debug_log << endl;
		adtFile << (*mtex);
		//sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "ha");
	} else { mhdr->offsMCIN = NULL; }
	if(mmdx) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mmdx...");
		mhdr->offsMMDX = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mmdx);
	} else { mhdr->offsMMDX = NULL; }
	if(mmid) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mmid...");
		mhdr->offsMMID = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mmid);
	} else { mhdr->offsMMID = NULL; }
	if(mwmo) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mwmo...");
		mhdr->offsMWMO = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mwmo);
	} else { mhdr->offsMWMO = NULL; }
	if(mwid) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mwmo...");
		mhdr->offsMWID = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mwid);
	} else { mhdr->offsMWID = NULL; }
	if(mddf) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mddf...");
		mhdr->offsMDDF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mddf);
	} else { mhdr->offsMDDF = NULL; }
	if(modf) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing modf...");
		mhdr->offsMODF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*modf);
	} else { mhdr->offsMODF = NULL; }

	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mcnk...");
	mcnk->mcin = mcin; //update link
	adtFile << (*mcnk); 
	if(mfbo) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mfbo...");
		mhdr->offsMFBO = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mfbo);
	} else { mhdr->offsMFBO = NULL; }

	adtFile.seekp(32768, std::ios_base::cur);

	if(mh2o) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mh2o...");
		mhdr->offsMH2O = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mh2o);
	} else { mhdr->offsMH2O = NULL; }
	if(mtxf) {
		sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mtxf...");
		mhdr->offsMTXF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mtxf);
	} else { mhdr->offsMTXF = NULL; }

	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mhdr...");
	adtFile.seekp(MHDR_OFFSET - sizeof(chunkHeader)); //reserving, mhdr written at the end
	adtFile << (*mhdr);
	sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Writing mcin...");
	adtFile << (*mcin);

    sLogger->OutMessage(Logger::LOG_LEVEL_NORMAL, "Done writing adt data");
}

void adt::AllWaterMCLQ(float height)
{
    for (int i = 0; i < MCNK::ENTRY_COUNT; i++) {
		mcnk->entries[i].mclq = new MCLQ(height, 0.0f, 0x04, 0x00);
		mcnk->entries[i].header.flags |= MCNK::FLAG_LQ_RIVER;
	}
}