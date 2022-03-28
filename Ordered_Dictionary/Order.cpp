//-----------------------------------------------------------------------------
// Dmitrius Agoston
// Dagoston
// pa7
//
// Order.cpp
// File that puts given strings into an ordered dictionary
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

    int line_count;
    ifstream in;
    ofstream out;
    std::string line;
    Dictionary Dict;

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

   // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read each line of input file, then add to dictionary 
    line_count = 0;
    while( getline(in, line) )  {
        line_count++; 
        // add to dictionary
        Dict.setValue(line, line_count);
    }
    // print dictionary
    out << Dict << endl;
    out << Dict.pre_string() << endl;

    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
