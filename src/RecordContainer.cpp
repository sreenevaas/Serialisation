#include "RecordContainer.hpp"

using namespace std;

bool RecordContainer :: findNumber(string & s) 
{ 
    int num = atoi(s.c_str());
    if (num == 0 && s[0] != '0')
    {
        return false;
    }
    return true; 
}

Record * RecordContainer :: objectify(vector<string> & recordData)
{
    if(recordData.size() == 6)
    {
        Recs = QuoteRecord::getInstance();
        Recs->objectify(recordData);
        return Recs;
    }
    else if(recordData.size() == 4)
    {
        if(findNumber(recordData[3]))
        {
            Recs = SignalRecord::getInstance();
            Recs->objectify(recordData);
            return Recs; 
        }
        else
        {
            Recs = TradeRecord::getInstance();
            Recs->objectify(recordData);   
            return Recs; 
        }
    }
    else
    {
        cout << "!!!TradeRecord[3]: "<< recordData[3] << endl;
        Recs = TradeRecord::getInstance();
        Recs->objectify(recordData); 
        return Recs;  
    }
}

Record * RecordContainer :: deObjectify(shared_ptr<ifstream> inpStream, string recordSymbol, string &data)
{
    short objType = 0;
    inpStream->read(reinterpret_cast<char *>(&objType), sizeof(short));

    if(objType == QUOTERECORD)
    {
        Recs = QuoteRecord::getInstance();
        Recs->deObjectify(inpStream, recordSymbol, data);
        return Recs;
    } 
    else if(objType == SIGNALRECORD)
    {
        Recs = SignalRecord::getInstance();
        Recs->deObjectify(inpStream, recordSymbol, data);
        return Recs;
    }
    else if(objType == TRADERECORD)
    {
        Recs = TradeRecord::getInstance();
        Recs->deObjectify(inpStream, recordSymbol, data);
        return Recs;
    }
    else
    {
        cout << " Invalid data Read " << endl;
        return Recs; 
    }
}