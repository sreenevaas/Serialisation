#ifndef RecordContainer_HPP
#define RecordContainer_HPP

#include "Record.hpp"

class RecordContainer
{
    Record *Recs;
    bool findNumber(std::string & s);
public:
    RecordContainer()
    {
        Recs = NULL;
    }
    Record * objectify(std::vector<std::string> & recordData);
    Record * deObjectify(std::shared_ptr<std::ifstream> inpStream, std::string recordSymbol, std::string &data);
};

#endif