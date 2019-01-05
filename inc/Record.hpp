
#ifndef Record_HPP
#define Record_HPP
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <dirent.h>

typedef unsigned long long int uInt64;

enum RecordTypes
{
    QUOTERECORD,
    TRADERECORD,
    SIGNALRECORD
};

class Record
{
public:
    char datetime[25];
    Record()
    {
    }
    virtual void csvWrite(std::shared_ptr<std::ofstream> oup, std::string &data) =0;
    virtual void binWrite(std::shared_ptr<std::ofstream> oup, uInt64 serialNo) = 0;
    virtual void objectify(std::vector<std::string> & record) = 0;
    virtual void deObjectify(std::shared_ptr<std::ifstream> inps, std::string symbol, std::string &data) = 0;

};

class QuoteRecord : public Record
{
    static QuoteRecord *QRObj;
    QuoteRecord():Record()
    {  
    }
public:
    double bid;
    double ask;
    int bSize;
    int aSize;
    
    static QuoteRecord * getInstance()
    {
        if (QRObj == NULL){
            QRObj = new QuoteRecord();
        }
        return QRObj;
    }
    
    void csvWrite(std::shared_ptr<std::ofstream> oup, std::string &data);
    void binWrite(std::shared_ptr<std::ofstream> oup, uInt64 serialNo);
    void objectify(std::vector<std::string> & record);
    void deObjectify(std::shared_ptr<std::ifstream> inps, std::string symbol,
         std::string &data);
};



class TradeRecord : public Record
{
    static TradeRecord *TRObj;
    TradeRecord():Record()
    { 
    }
public:
    double price;
    char condition;
   
    void csvWrite(std::shared_ptr<std::ofstream> oup, std::string &data);
    void binWrite(std::shared_ptr<std::ofstream> oup, uInt64 serialNo);
    void objectify(std::vector<std::string> & record);
    void deObjectify(std::shared_ptr<std::ifstream> inps, std::string symbol,
            std::string &data);
    
    static TradeRecord * getInstance()
    {
        if (TRObj == NULL){
            TRObj = new TradeRecord();
        }
        return TRObj;
    }
};


class SignalRecord: public Record
{
    static SignalRecord *SRObj;
    SignalRecord():Record()
    {
    }
public:
    double value;
    int code;
    
    void csvWrite(std::shared_ptr<std::ofstream> oup, std::string &data);
    void binWrite(std::shared_ptr<std::ofstream> oup, uInt64 serialNo);
    void objectify(std::vector<std::string> & record);
    void deObjectify(std::shared_ptr<std::ifstream> inps, std::string symbol, std::string &data);
    static SignalRecord * getInstance()
    {
        if (SRObj == NULL){
            SRObj = new SignalRecord();
        }
        return SRObj;
    }
};

#endif