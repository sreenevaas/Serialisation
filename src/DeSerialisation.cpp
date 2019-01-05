
#include "DeSerialisation.hpp"
using namespace std;
string DeSerialisation::getFileExtension(const string& s)
{
   size_t i = s.rfind('.', s.length());
   if (i != string::npos) {
      return(s.substr(i+1, s.length() - i));
   }
   return("");
}

/*To Get the List of files from bin directory*/
void DeSerialisation :: GetBinFiles(void)
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
            string name = dirp->d_name;
            string ext ="";
            ext = getFileExtension(name);
            if(ext.compare("bin") != 0)
            {
                continue;
            }
            binFiles.push_back(string(dirp->d_name));
        }
    }
    closedir(dp);
}

void DeSerialisation :: deSerialize()
{
    shared_ptr<ifstream>inps;
    string data = "";
    long long int position = 0;
    vector<string>::iterator it;
    shared_ptr<ofstream> oup(new ofstream); //Stream to Handle CSV File
    oup->open(CSVfileName);
    if(!oup)
    {
		cout << "Error in Opening file..."<<endl;
        return;
    }
    GetBinFiles();
    binFileStreams.clear();
    for(it = binFiles.begin(); it < binFiles.end(); it++)
    {
        shared_ptr<ifstream> inp(new std::ifstream);  //Stream to Handle Binary File
        string symbol ="";
        string filePath = "./bin_files/";
        filePath.append(*it);
        symbol = *it;
        symbol.erase(symbol.find_last_of("."), string::npos);  //Extracting Symbols from File Names
        inp->open(filePath.c_str(), ios::binary|ios::out);
        if(!inp)
        {
	    cout << "Error in Opening file..."<<endl;
        }
        binFileStreams.insert(make_pair(symbol, inp));
    }
    while(!binFileStreams.empty())
    {
        for(st = binFileStreams.begin(); st != binFileStreams.end(); st++)
        {
            inps = st->second;
            data.clear();
            position = 0;
            if(!inps->good())
            {
                inps->close();
                // cout << "erased: " << st->first << endl;
                binFileStreams.erase(st->first);   //Removing completed files streams from map
                break;
            }
            position = inps->tellg();
            inps->read(reinterpret_cast<char *>(&serialNo), sizeof(uInt64));
            if(nextNo == serialNo)   //Logic to De-serialize
            {
                Record *Rec = deSerialObj.deObjectify(inps, st->first, data);
                Rec->csvWrite(oup, data);
                nextNo += 1;
            }
            else
            {
                inps->seekg(position, ios::beg);  
            }
        }
    }
    // oup->flush();
    oup->close();
    // cout << "Endof DeSerialisation at Record: " << nextNo << endl;
}
