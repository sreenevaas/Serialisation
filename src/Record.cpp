#include "Record.hpp"
#include <iomanip>
using namespace std;

QuoteRecord * QuoteRecord :: QRObj = NULL;
TradeRecord * TradeRecord:: TRObj = NULL;
SignalRecord *SignalRecord :: SRObj = NULL;

void QuoteRecord :: objectify(vector<string> & record)
{
    record[0].copy(this->datetime, record[0].length()) ;
    this->bid = atof(record[2].c_str());
    this->ask = atof(record[3].c_str());
    this->bSize = atoi(record[4].c_str());
    this->aSize = atoi(record[5].c_str());
}

void QuoteRecord :: deObjectify(shared_ptr<ifstream> inps, string symbol, string &data)
{
    string dateTime = "";
    string bid = "";
    string ask = "";
    stringstream stream1;
    stringstream stream2;
    inps->read(reinterpret_cast<char *>(this->datetime), sizeof(this->datetime));
    inps->read(reinterpret_cast<char *>(&(this->bid)), sizeof(this->bid));
    inps->read(reinterpret_cast<char *>(&(this->ask)), sizeof(this->ask));
    inps->read(reinterpret_cast<char *>(&(this->bSize)), sizeof(this->bSize));
    inps->read(reinterpret_cast<char *>(&(this->aSize)), sizeof(this->aSize));
    dateTime = this->datetime;
    data.append(dateTime);
    data.append(",");
    data.append(symbol);
    data.append(",");
    stream1 << fixed << setprecision(4) << this->bid;
    bid = stream1.str();
    data.append(bid);
    data.append(",");
    stream2 << fixed << setprecision(4) << this->ask;
    ask = stream2.str();
    data.append(ask);
    // data.append(to_string(this->ask));
    data.append(",");
    data.append(to_string(this->bSize));
    data.append(",");
    data.append(to_string(this->aSize));
    data.append("\n");
}
void QuoteRecord :: binWrite(shared_ptr<ofstream> oup, uInt64 serialNo)
{
    short RecType = QUOTERECORD;
    oup->write(reinterpret_cast<char *>(&serialNo), sizeof(uInt64));
    oup->write(reinterpret_cast<char *>(&(RecType)), sizeof(RecType));
    oup->write(reinterpret_cast<char *>(this->datetime), sizeof(this->datetime));
    oup->write(reinterpret_cast<char *>(&(this->bid)), sizeof(this->bid));
    oup->write(reinterpret_cast<char *>(&(this->ask)), sizeof(this->ask));
    oup->write(reinterpret_cast<char *>(&(this->bSize)), sizeof(this->bSize));
    oup->write(reinterpret_cast<char *>(&(this->aSize)), sizeof(this->aSize));
}

void QuoteRecord :: csvWrite(shared_ptr<ofstream> oup, string &data)
{
    oup->write(data.c_str(), data.length());
}



void TradeRecord:: objectify(vector<string> & record)
{
    record[0].copy(this->datetime , record[0].length()) ;
    this->price = atof(record[2].c_str());
    this->condition = *(record[3].c_str());
}

void TradeRecord :: deObjectify(shared_ptr<ifstream> inps, string symbol, string &data)
{
    stringstream stream;
   
    string dateTime = "";
    string price = "";
    inps->read(reinterpret_cast<char *>(this->datetime), sizeof(this->datetime));
    inps->read(reinterpret_cast<char *>(&(this->price)), sizeof(this->price));
    inps->read(reinterpret_cast<char *>(&(this->condition)), sizeof(this->condition));
    dateTime = this->datetime;
    data.append(dateTime);
    data.append(",");
    data.append(symbol);
    data.append(",");
    stream << fixed << setprecision(4) << this->price;
    price = stream.str();
    data.append(price);
    data.append(",");
    string cond(1, this->condition);
    data.append(cond);
    data.append("\n");
}

void TradeRecord :: binWrite(shared_ptr<ofstream> oup, uInt64 serialNo)
{
    short RecType = TRADERECORD;
    oup->write(reinterpret_cast<char *>(&serialNo), sizeof(uInt64));
    oup->write(reinterpret_cast<char *>(&(RecType)), sizeof(RecType));
    oup->write(reinterpret_cast<char *>(this->datetime), sizeof(this->datetime));
    oup->write(reinterpret_cast<char *>(&(this->price)), sizeof(this->price));
    oup->write(reinterpret_cast<char *>(&(this->condition)), sizeof(this->condition));
}

void TradeRecord :: csvWrite(shared_ptr<ofstream> oup, string &data)
{
    oup->write(data.c_str(), data.length());
}

void SignalRecord :: objectify(vector<string> & record)
{
    record[0].copy(this->datetime , record[0].length()) ;
    this->value = atof(record[2].c_str());
    this->code = atoi(record[3].c_str()); 
}

void SignalRecord :: deObjectify(shared_ptr<ifstream> inps, string symbol, string &data)
{
    string dateTime = "";
    string value = "";
    stringstream stream;
    inps->read(reinterpret_cast<char *>(this->datetime), sizeof(this->datetime));
    inps->read(reinterpret_cast<char *>(&(this->value)), sizeof(this->value));
    inps->read(reinterpret_cast<char *>(&(this->code)), sizeof(this->code));
    dateTime = this->datetime;
    data.append(dateTime);
    data.append(",");
    data.append(symbol);
    data.append(",");
    stream << fixed << setprecision(4) << this->value;
    value = stream.str();
    data.append(value);
    // data.append(to_string(this->value));
    data.append(",");
    data.append(to_string(this->code));
    data.append("\n");
}

void SignalRecord :: binWrite(shared_ptr<ofstream> oup, uInt64 serialNo)
{
    short RecType = SIGNALRECORD;
    oup->write(reinterpret_cast<char *>(&serialNo), sizeof(uInt64));
    oup->write(reinterpret_cast<char *>(&(RecType)), sizeof(RecType));
    oup->write(reinterpret_cast<char *>(this->datetime), sizeof(this->datetime));
    oup->write(reinterpret_cast<char *>(&(this->value)), sizeof(this->value));
    oup->write(reinterpret_cast<char *>(&(this->code)), sizeof(this->code));
}

void SignalRecord :: csvWrite(shared_ptr<ofstream> oup, string &data)
{
    oup->write(data.c_str(), data.length());
}