/*
 * Lexer.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: robbe
 */

#include "Lexer.h"
#include <iostream>

using namespace std;

namespace lexer{


vector<string> string_to_vec(string input){

	stringstream ss (input);
	return string_to_vec(ss);
}


vector<string> string_to_vec(stringstream&  input){

    istream_iterator<std::string> begin(input);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	return vstrings;
}

vector<string> file_to_vec(string file){

    string instruction = "";
    vector<string> myString;
    ifstream inFile;
    inFile.open(file);

    if (inFile.is_open()){

        //Read until no more lines in text file to read
        while (getline(inFile, instruction))
        {

            istringstream ss(instruction);
            string token = "";
            //Separate string based on commas and white spaces
            while(getline(ss,token,' ')){

                myString.push_back(token);
            }

        }
    }
   return myString;
}
}

