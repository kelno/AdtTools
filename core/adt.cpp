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
            sLogger->Out(Logger::LOG_LEVEL_ERROR, "Could not get adt file in memory, aborting.");
            exit(1);
        }
    }
    sLogger->Out(Logger::LOG_LEVEL_NORMAL, "Extracting adt data");

    //reset read position at file start, to be sure
	adtFile.seekg(0, std::ios_base::beg); 
	try {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mver...");
		mver = new MVER(adtFile);
	} catch (char* e) {
        sLogger->Out(Logger::LOG_LEVEL_ERROR, "Exception when constructing MVER : %s", e);
		sLogger->Out(Logger::LOG_LEVEL_ERROR, "Is this an adt file? Aborting...");
		exit(1);
	}

	try 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mhdr...");
		mhdr = new MHDR(adtFile, MHDR_OFFSET - sizeof(chunkHeader));
	} catch (char* e) {
        sLogger->Out(Logger::LOG_LEVEL_ERROR, "Exception when constructing MHDR : %s", e);
        sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Read position %xh", (int)adtFile.tellg());
		sLogger->Out(Logger::LOG_LEVEL_ERROR, "Cannot continue, aborting...");
		exit(1);
	}

	//which one can be empty ?
	if (mhdr->offsMCIN) 
    {
		try {
			sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mcin...");
			if (mhdr->offsMCIN) 
                mcin = new MCIN(adtFile, MHDR_OFFSET + mhdr->offsMCIN);
		} catch (char* e) {
            sLogger->Out(Logger::LOG_LEVEL_ERROR, "Exception when constructing MCIN : %s", e);
		}
	}
	if (mhdr->offsMTEX) 
    {
		try {
			sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mtex...");
			mtex = new MTEX(adtFile, MHDR_OFFSET + mhdr->offsMTEX);
			//std::cout << mtex->debug_log << endl;
		} catch (char* e) {
            sLogger->Out(Logger::LOG_LEVEL_ERROR, "Exception when constructing MTEX : %s", e);
		}
	}  else
		mtex = nullptr;

	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mmdx...");
	if (mhdr->offsMMDX) mmdx = new MMDX(adtFile, MHDR_OFFSET + mhdr->offsMMDX);
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mmid...");
	if (mhdr->offsMMID) mmid = new MMID(adtFile, MHDR_OFFSET + mhdr->offsMMID);
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mwmo...");
	if (mhdr->offsMWMO) mwmo = new MWMO(adtFile, MHDR_OFFSET + mhdr->offsMWMO);
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mwid...");
	if (mhdr->offsMWID) mwid = new MWID(adtFile, MHDR_OFFSET + mhdr->offsMWID);
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mddf...");
	if (mhdr->offsMDDF) mddf = new MDDF(adtFile, MHDR_OFFSET + mhdr->offsMDDF);
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting modf...");
	if (mhdr->offsMODF) modf = new MODF(adtFile, MHDR_OFFSET + mhdr->offsMODF);

	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mcnk...");
	mcnk = new MCNK(adtFile, mcin);

	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mfbo...");
	if (mhdr->offsMFBO)	mfbo = new MFBO(adtFile, MHDR_OFFSET + mhdr->offsMFBO);
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mh2o...");
	if (mhdr->offsMH2O)	mh2o = new MH2O(adtFile, MHDR_OFFSET + mhdr->offsMH2O);
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Extracting mtxf...");
	if (mhdr->offsMTXF)	mtxf = new MTXF(adtFile, MHDR_OFFSET + mhdr->offsMTXF);
	sLogger->Out(Logger::LOG_LEVEL_NORMAL, "Extracting done");

	//TODO ValidityCheck
}

adt::~adt()
{
    //todo, free memory
}

void adt::WriteToDisk(fstream& adtFile)
{
	sLogger->Out(Logger::LOG_LEVEL_NORMAL, "Writing adt data");
    //set write position at file beginning
	adtFile.seekp(0, std::ios_base::beg); 
	adtFile << (*mver);
    //reserving space for mhdr, it will be written later.
	adtFile.seekp(sizeof(MHDR) + sizeof(chunkHeader), std::ios_base::cur);

	mhdr->offsMCIN = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
    //reserving space for mcin, it will be written later
	adtFile.seekp(sizeof(MCIN) + sizeof(chunkHeader), std::ios_base::cur); 
	
	if(mtex) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mtex...");
		mhdr->offsMTEX = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mtex);
	} else { mhdr->offsMCIN = NULL; }

	if(mmdx) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mmdx...");
		mhdr->offsMMDX = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mmdx);
	} else { mhdr->offsMMDX = NULL; }

	if(mmid) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mmid...");
		mhdr->offsMMID = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mmid);
	} 
    else { mhdr->offsMMID = NULL; }

	if(mwmo) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mwmo...");
		mhdr->offsMWMO = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mwmo);
	} else { mhdr->offsMWMO = NULL; }

	if(mwid) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mwmo...");
		mhdr->offsMWID = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mwid);
	} else { mhdr->offsMWID = NULL; }

	if(mddf) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mddf...");
		mhdr->offsMDDF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mddf);
	} else { mhdr->offsMDDF = NULL; }

	if(modf) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing modf...");
		mhdr->offsMODF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*modf);
	} else { mhdr->offsMODF = NULL; }

	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mcnk...");
	mcnk->mcin = mcin; //update link
	adtFile << (*mcnk); 
	if(mfbo) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mfbo...");
		mhdr->offsMFBO = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mfbo);
	} else { mhdr->offsMFBO = NULL; }

	adtFile.seekp(32768, std::ios_base::cur);

	if(mh2o) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mh2o...");
		mhdr->offsMH2O = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mh2o);
	} else { mhdr->offsMH2O = NULL; }

	if(mtxf) 
    {
		sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mtxf...");
		mhdr->offsMTXF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mtxf);
	} else { mhdr->offsMTXF = NULL; }

    //now write the data we skipped
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mhdr...");
	adtFile.seekp(MHDR_OFFSET - sizeof(chunkHeader));
	adtFile << (*mhdr);
	sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Writing mcin...");
	adtFile << (*mcin);

    sLogger->Out(Logger::LOG_LEVEL_NORMAL, "Done writing adt data");
}

void adt::AllWaterMCLQ(float height)
{
    for (int i = 0; i < MCNK::ENTRY_COUNT; i++) {
		mcnk->entries[i].mclq = new MCLQ(height, 0.0f, MCLQ_FLAG1_UNK_3, MCLQ_FLAG2_NONE);
		mcnk->entries[i].header.flags |= MCNK::FLAG_LQ_RIVER;
	}
}