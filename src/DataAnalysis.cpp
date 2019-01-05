//
//  DataAnalysis.cpp
//  QB_Project
//
//  Created by Srinivasa Rao M on 24/12/18.
//  Copyright © 2018 Srinivasa Rao M. All rights reserved.
//
#include "Serialisation.hpp"
#include "DeSerialisation.hpp"
#include<ctime>
using namespace std;

int main(int argc, const char * argv[])
{
    time_t start, stop, startTime, endTime; 
    double timeTaken = 0;
    start = clock();
    startTime = start;
    Serialisation SH("q.csv");
    DeSerialisation DSH("out.csv");

    SH.serialize(); /*Parsing CSV file and Serialisation*/

    stop = clock();
    timeTaken = double(stop - start)/double(CLOCKS_PER_SEC)*1000;
    cout << "Time Taken for serialize and writing data to Binary File:  "<< timeTaken << " ms"<< endl;
    start = clock();

    DSH.deSerialize();/*Parsing BIN files and De-Serialisation*/

    stop = clock(); 
    endTime = stop;
    timeTaken = double(stop - start)/double(CLOCKS_PER_SEC)*1000;
    cout << "Time Taken for Deserialize and writing back to CSV File:  "<< timeTaken<< " ms"<< endl;
    timeTaken = double(endTime - startTime)/double(CLOCKS_PER_SEC)*1000;
    cout << "Total Time Taken:  "<< timeTaken<< " ms"<< endl; 
    cout << "Please Verify out.csv File!!!!" << endl;
    return 0;
}
