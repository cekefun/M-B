/*
 * Grammar.h
 *
 *  Created on: Sep 29, 2016
 *      Author: cedric
 */

#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include <vector>
#include <set>
#include <map>
#include <string>

using symbol = std::string;
using word = std::vector<symbol>;

class Grammar {
public:
	Grammar();
	symbol GetStart();
	bool SetStart(symbol);
	std::vector<symbol> GetVariables();
	bool AddVariable(symbol);
	void DeleteVariable(symbol);
	bool IsVariable(symbol);
	std::vector<symbol> GetTerminals();
	bool AddTerminal(symbol);
	void DeleteTerminal(symbol);
	bool IsTerminal(symbol);
	std::map<symbol,std::vector<word>> GetRules();
	bool AddRule(symbol,word);
	void DeleteRule(symbol,word);
	bool IsRule(symbol,word);
	bool ParseGrammar(std::string);
	bool SaveGrammar(std::string);
	void print(std::ostream& );
	//friend std::ostream& operator<<(std::ostream&, const Grammar&);

private:
	symbol Start;
	std::vector<symbol> Variables;
	std::vector<symbol> Terminals;
	std::map<symbol,std::vector<word>> Rules;
};


#endif /* GRAMMAR_H_ */
