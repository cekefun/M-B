/*
 * grammar.cpp
 *
 *  Created on: 9-okt.-2015
 *      Author: C�dric
 */

#include "grammar.h"

grammar::grammar() {
	startSymbol = '0';
}

grammar::grammar(const std::set<std::string> inputvariables,const std::set<std::string> inputterminals,const std::string start){
	/*
	 * constructor of the grammar given the variables, terminals and startsymbol.
	 */

	//The variables and terminals can't be the same.
	for(std::set<std::string>::iterator VarIt = inputvariables.begin(); VarIt != inputvariables.end();VarIt++){
		std::string Var = *VarIt;
		if(inputterminals.find(Var) != inputterminals.end()){
			std::cout<<"Variables and terminals have at least 1 character duplicate. This is not allowed."<<std::endl;
			startSymbol = "0";
			return;
		}
	}

	//the startsymbol has to be in the variables.
	if(inputvariables.find(start) == inputvariables.end()){
		std::cout<<"The startsymbol has to be a given variable."<<std::endl;
		startSymbol = "0";
		return;
	}

	startSymbol = start;
	variables = inputvariables;
	terminals = inputterminals;
}

bool invalidRules(const std::map<std::string,std::set<std::vector<std::string> > > &irules,
		const std::set<std::string> &inputvariables,const std::set<std::string> &inputterminals)
{
	std::map<std::string,std::set<std::vector<std::string> > >::const_iterator it;
	for( it=irules.begin(); it != irules.end(); ++it )
	{
		if(inputvariables.find(it->first) == inputvariables.end()) return true;
		for(std::set<std::vector<std::string> >::const_iterator it2 = it->second.begin();
				it2 != it->second.end(); it2++)
		{
			for(unsigned int i=0; i < it2->size(); i++)
			{
				if( !(*it2)[i].empty() and
						inputvariables.find((*it2)[i]) == inputvariables.end() and
						inputterminals.find((*it2)[i]) == inputterminals.end())
					return true;
			}
		}
	}
	return false;
}

grammar::grammar(const std::set<std::string> &inputvariables,
		const std::set<std::string> &inputterminals,const std::string &start,
		const std::map<std::string,std::set<std::vector<std::string> > > &irules) {
	/*
	 * constructor of the grammar given the variables, terminals and startsymbol.
	 */

	//The variables and terminals can't be the same.
	for(std::set<std::string>::iterator VarIt = inputvariables.begin(); VarIt != inputvariables.end();VarIt++){
		std::string Var = *VarIt;
		if(inputterminals.find(Var) != inputterminals.end()){
			std::cout<<"Variables and terminals have at least 1 character duplicate. This is not allowed."<<std::endl;
			startSymbol = "0";
			return;
		}
	}

	//the startsymbol has to be in the variables.
	if(inputvariables.find(start) == inputvariables.end()){
		std::cout<<"The startsymbol has to be a given variable."<<std::endl;
		startSymbol = "0";
		return;
	}

	if( invalidRules(irules, inputvariables, inputterminals) )
	{
		std::cout<<"The rules are invalid."<<std::endl;
		return;
	}

	startSymbol = start;
	variables = inputvariables;
	terminals = inputterminals;
	rules = irules;
}

//Is the grammar valid? Any invalidities change the grammar in one with a 0 as start, no terminals and no variables
bool grammar::IsEmpty() const{
	if(variables.empty()&&terminals.empty()&&startSymbol == "0"){
		return true;
	}
	else{
		return false;
	}
}

std::set<std::vector<std::string> > grammar::getRules(const std::string var){
	return rules[var];
}

std::string grammar::getStart() const{
	return startSymbol;
}

bool grammar::isRule(const std::string symbol, const std::vector<std::string> result){
	for(std::set<std::vector<std::string> >::iterator string = rules[symbol].begin(); string != rules[symbol].end(); string++){
		if (result == *string){
			return true;
		}
	}
	return false;
}

bool grammar::addRule(const std::string symbol, std::vector<std::string> string){
	/*
	 * adds a rule to the the grammar
	 */
	//head has to be a variable
	if(variables.find(symbol) == variables.end()){
		std::cout<<"The symbol is not part of the variables."<<std::endl;
		return false;
	}

	//body has to have only variables and terminals
	for(std::vector<std::string>::iterator sym = string.begin(); sym != string.end(); sym++){
		if(variables.find(*sym) == variables.end() and terminals.find(*sym) == terminals.end()){
			std::cout<<"At least 1 character from the body is neither a variable nor a terminal."<<std::endl;
			return false;
		}
	}
	rules[symbol].insert(string);
	return true;
}

bool grammar::isTerminal(const std::string x) const{
	if(terminals.find(x) == terminals.end()){
		return false;
	}
	return true;
}

std::set<std::string> grammar::getVariables() const{
	return variables;
}

void grammar::deleteVariable(const std::string toDelete){
	variables.erase(toDelete);
}

bool grammar::save(const char* file){
	std::ofstream doc;
	doc.open(file);
	//if the doc doesn't open, it won't save
	if(!doc.is_open()){
		return false;
	}

	doc<<"<?xml version=\"1.0\" ?>"<<std::endl;
	doc<<"<CFG>"<<std::endl;

	doc<<"\t"<<"<Variables>"<<std::endl;
	doc<<"\t\t";
	for(std::set<std::string>::iterator varIt = variables.begin(); varIt != variables.end();varIt++){
		std::set<std::string>::reverse_iterator rit = variables.rbegin();
		if((*varIt) == (*rit)){
			doc<<*varIt;
			continue;
		}
		doc<<*varIt<<"|";
	}
	doc<<std::endl;
	doc<<"\t\t"<<"<StartSymbol>" << startSymbol<<"</StartSymbol>"<<std::endl;
	doc<<"\t"<<"</Variables>"<<std::endl;

	doc<<"\t"<<"<Terminals>"<<std::endl;
	doc<<"\t\t";
	for(std::set<std::string>::iterator terIt = terminals.begin(); terIt != terminals.end();terIt++){
		if(terIt == terminals.begin()){
			doc<<*terIt;
			continue;
		}
		doc<<"|"<<*terIt;
	}
	doc<<std::endl;
	doc<<"\t"<<"</Terminals>"<<std::endl;

	doc<<"\t"<<"<Productions>"<<std::endl;
	for(std::map<std::string,std::set<std::vector<std::string> > >::iterator mapIt = rules.begin(); mapIt != rules.end();mapIt++){
		doc<<"\t\t"<<"<Rule LHS=\""<<mapIt->first<<"\" RHS= \"";
		for(std::set<std::vector<std::string> >::iterator vecIt = mapIt->second.begin(); vecIt != mapIt->second.end(); vecIt++){
			if(vecIt != mapIt->second.begin()){
				doc<<"|";
			}
			for(auto strIt = vecIt->begin(); strIt != vecIt->end();strIt++){
				if(strIt == vecIt->begin()){
					doc<<*strIt;
				}
				else{
					doc<<" "<<*strIt;
				}
			}
		}
		doc<<"\"/>"<<std::endl;
	}
	doc<<"\t"<<"</Productions>"<<std::endl;

	doc<<"</CFG>"<<std::endl;

	doc.close();
	return true;
}

pda grammar::toPDA()
{
	std::set<std::string> states;
	std::set<std::string> alphabet;
	std::set<std::string> stackSymbols;
	std::vector<Transition> transitions;
	std::string startState;
	std::string startSymbolp;

	states.insert("Q");
	startState = "Q";
	startSymbolp = startSymbol;

	std::set<std::string>::iterator it;
	for( it=terminals.begin(); it != terminals.end(); ++it )
	{
		alphabet.insert((*it));
		stackSymbols.insert((*it));
		std::string state("Q");
		std::string inputSymbol((*it));
		std::string stackSymbol((*it));
		std::string nextState("Q");
		std::vector<std::string> pushSymbols;
		Transition t(state, inputSymbol, stackSymbol, nextState, pushSymbols);
		transitions.push_back(t);
	}
	for( it=variables.begin(); it != variables.end(); ++it )
	{
		stackSymbols.insert((*it));
		std::set<std::vector<std::string> >::iterator it2;
		for( it2=rules[(*it)].begin(); it2 != rules[(*it)].end(); ++it2 )
		{
			std::string state("Q");
			std::string inputSymbol;
			std::string stackSymbol((*it));
			std::string nextState("Q");
			std::vector<std::string> pushSymbols(*it2);
			Transition t(state, inputSymbol, stackSymbol, nextState, pushSymbols);
			transitions.push_back(t);
		}
	}
	return pda(states, alphabet, stackSymbols, transitions, startState, startSymbolp);
}
