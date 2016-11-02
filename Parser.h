/*
 * Parser.h
 *
 *  Created on: 5-nov.-2015
 *      Author: Raphael
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "pda.h"
#include "grammar.h"
#include "tinyxml/tinyxml.h"

class Parser {
public:
	Parser();
	bool ParsePDA(const char*, pda&);
	bool ParseGrammar(const char*, grammar&);
};

#endif /* PARSER_H_ */
