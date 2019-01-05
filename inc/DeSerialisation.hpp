#ifndef Deserialisation_HPP
#define Deserialisation_HPP

#include "RecordContainer.hpp"

class DeSerialisation
{
    std::string CSVfileName;
    std::vector<std::string> binFiles;
    std::vector<std::string> binRecord;
    uInt64 serialNo;
    uInt64 nextNo;
    RecordContainer deSerialObj;
    std::map< std::string, std::shared_ptr<std::ifstream> > binFileStreams;
    std::map< std::string, std::shared_ptr<std::ifstream> >::iterator st;
    std::string getFileExtension(const std::string& s);

public: /*Need to check*/
    DeSerialisation(std::string name = "out.csv"):CSVfileName(name)
    {
        serialNo = 0X01;
        nextNo = 0x01;
    }
    void deSerialize(void);
    std::string CreateBinFileName(const char * binFile);
    void GetBinFiles(void);
};

#endif