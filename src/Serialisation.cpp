#include "Serialisation.hpp"
using namespace std;

uInt64 Serialisation::serialNo = 1;
/* To create Filename with .bin extension*/
string Serialisation :: createBinFileName(const char * binFile)
{
    string fileName = "./bin_files/";
    fileName.append(binFile);
    fileName.append(".bin");
    return fileName;
}
/* To Write data into binary files*/
void Serialisation::writeToBinFile(vector<string> & record)
{
    string binFileName = "";
    binFileName = createBinFileName(record[1].c_str());
    pos = binFileStreams.find(binFileName);
    if(pos == binFileStreams.end())
    {
        shared_ptr<ofstream> oup(new std::ofstream);
        oup->open(binFileName, ios::binary| ios::out| ios::app);
        if(!oup)
        {
            cout << "Error in Opening file..."<<endl;
        }
        binFileStreams.insert(make_pair(record[1], oup));
        pos = binFileStreams.find(record[1]);
    }
    Record * Rec = serialObj.objectify(record);
    Rec->binWrite(pos->second, serialNo);
    ++serialNo;
}

/*Parsing CSV File and writng records to bin files*/
void Serialisation :: serialize(void)
{
    string line = "";
    vector<string>::iterator it;
    ifstream inp(CSVFileName);
    if(!inp)
    {
		cout<<"Error in Opening file..."<<endl;
    }
    removeBinFiles();  //Clean Bin Directory
    while(getline(inp, line))
    {
        stringstream   lineStream(line);
        string         cell;
        CSVRecord.clear();
        while(std::getline(lineStream, cell, ','))
        {
            CSVRecord.push_back(cell);    
        }
        writeToBinFile(CSVRecord);
    }
    for(pos = binFileStreams.begin(); pos != binFileStreams.end(); pos++)
    {
        // pos->second->flush();
        pos->second->close();
    }
    inp.close();
}

void Serialisation :: removeBinFiles()
{
    DIR *dp;
    string dir = "./bin_files/";
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL)
    {
        cout << "Error opening " << dir << endl;
        return;
    }
    while ((dirp = readdir(dp)) != NULL)
    {
        if(DT_DIR != dirp->d_type)
        {
            string name = dir;
            name.append(dirp->d_name);
            remove(name.c_str());
        }
    }
    closedir(dp);
    return;
}
