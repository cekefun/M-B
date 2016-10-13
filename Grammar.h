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
	std::set<symbol> GetVariables();
	bool AddVariable(symbol);
	void DeleteVariable(symbol);
	bool IsVariable(symbol);
	std::set<symbol> GetTerminals();
	bool AddTerminal(symbol);
	void DeleteTerminal(symbol);
	bool IsTerminal(symbol);
	std::map<symbol,std::set<word>> GetRules();
	bool AddRule(symbol,word);
	void DeleteRule(symbol,word);
	bool IsRule(symbol,word);
	bool ParseGrammar(std::string);
	bool SaveGrammar(std::string);
	void print(std::ostream& );
	//friend std::ostream& operator<<(std::ostream&, const Grammar&);

private:
	symbol Start;
	std::set<symbol> Variables;
	std::set<symbol> Terminals;
	std::map<symbol,std::set<word>> Rules;
};


#endif /* GRAMMAR_H_ */
