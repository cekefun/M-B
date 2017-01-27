/*
 * Lexer.h
 *
 *  Created on: Jan 12, 2017
 *      Author: robbe
 */

#ifndef LEXER_LEXER_H_
#define LEXER_LEXER_H_

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>

using namespace std;

namespace lexer{

vector<string> file_to_vec(string file);
vector<string> string_to_vec(string input);
vector<string> string_to_vec(stringstream&  input);

}

#endif /* LEXER_LEXER_H_ */
