/*
 * grammar.h
 *
 *  Created on: 9-okt.-2015
 *      Author: C�dric
 */

#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <vector>

class pda;

class grammar {
public:
	grammar();
	grammar(const std::set<std::string>,const std::set<std::string>,const std::string);
	grammar(const std::set<std::string>&,const std::set<std::string>&,const std::string&,
			const std::map<std::string,std::set<std::vector<std::string> > >&);
	bool IsEmpty() const;
	std::set<std::vector<std::string> > getRules(const std::string);
	bool isRule(const std::string, const std::vector<std::string>);
	std::string getStart() const;
	bool addRule(const std::string, const std::vector<std::string>);
	bool save(const char*);
	std::set<std::string> getVariables() const;
	bool isTerminal(const std::string) const;
	void deleteVariable(const std::string);
	pda toPDA();

private:
	std::set<std::string> variables;
	std::set<std::string> terminals;
	std::string startSymbol;
	std::map<std::string,std::set<std::vector<std::string> > > rules;

};

#endif /* GRAMMAR_H_ */
