
#ifndef Serialisation_HPP
#define Serialisation_HPP

#include "RecordContainer.hpp"

class Serialisation
{
    std::string CSVFileName;
    std::map<std::string, std::shared_ptr<std::ofstream> > binFileStreams;
    RecordContainer serialObj;
    static uInt64 serialNo;
    std::vector<std::string> CSVRecord;
    void writeToBinFile(std::vector<std::string> & record);
    std::map<std::string, std::shared_ptr<std::ofstream> >::iterator pos;
public: /*Need to check*/
    Serialisation(std::string name = "q.csv"):CSVFileName(name)
    {
    }
    void serialize(void);
    std::string createBinFileName(const char * binFile);
    void removeBinFiles();  
};
#endif