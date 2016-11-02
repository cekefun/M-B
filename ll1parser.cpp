#include "ll1parser.h"
#include <algorithm>
#include <sstream>

LL1Parser::LL1Parser(){
	grammar = new Grammar();
	error = "ERROR";
	EOS = "EOS";
}

LL1Parser::LL1Parser(Grammar* gram){
	setGrammar(gram);
}

bool LL1Parser::setGrammar(Grammar *gram){
	grammar = gram;
	Variables = gram->GetVariables();
	Terminals = gram->GetTerminals();

	EOS = "EOS";
	if (std::find(Terminals.begin(),Terminals.end(),EOS)!=Terminals.end()){
		for (int i = 1; i>0; i++){
			std::stringstream ss;
			ss<<"EOS"<<i;
			EOS = ss.str();
			if (std::find(Terminals.begin(),Terminals.end(),EOS)==Terminals.end()){
				break;
			}
		}
	}

	error = "ERROR";
	if (std::find(Terminals.begin(),Terminals.end(),error)!=Terminals.end() and std::find(Variables.begin(),Variables.end(),error)!=Variables.end()){
		for (int i = 1; i>0; i++){
			std::stringstream ss;
			ss<<"ERROR"<<i;
			error = ss.str();
			if (std::find(Terminals.begin(),Terminals.end(),error)==Terminals.end() and std::find(Variables.begin(),Variables.end(),error)!=Variables.end()){
				break;
			}
		}
	}
	CreateTable();
}

bool LL1Parser::CreateTable(){
	table = {};
	for (auto m = Variables.begin(); m < Variables.end(); m++){
		table.push_back({});
		for(auto n = Terminals.begin(); n < Terminals.end(); n++){
			word solution = {error};
			auto rules = grammar->GetRules()[*m];
			for (auto i = rules.begin(); i < rules.end(); i++){
				if (i->empty()){
					continue;
				}
				if (i->front()==*n){
					solution = *i;
					break;
				}
			}
			table.back().push_back(solution);
		}
		table.back().push_back({error});
	}
	return true;
}

bool LL1Parser::Print(std::ostream &out){
	out << "\t|";
	for (int i = 0; i < Terminals.size();i++){
		out<< Terminals.at(i)<<"\t | ";
	}
	out << EOS<<std::endl;

	for (int i = 0; i < Variables.size(); i++){
		out << Variables.at(i)<<"\t | ";
		for(int j = 0; j < Terminals.size(); j++){
			word rule = table.at(i).at(j);
			for(auto x = rule.begin(); x < rule.end(); x++){
				out <<" "<<*x;
			}
			out<<" | ";

		}

		out << table.at(i).back().front()<<std::endl;
	}
	return true;
}

bool LL1Parser::Parse(word toParse){
	if (toParse.empty()){
		std::cout<<"EMPTY PARSING NOT YET IMPLEMENTED"<<std::endl;
		return false;
	}
	std::vector<symbol> Stack;
	Stack.push_back(grammar->GetStart());

	word::iterator sym = toParse.begin();
	while(!Stack.empty()){
		if(sym == toParse.end()){
			return false;
		}
		symbol top = Stack.back();
		if(grammar->IsTerminal(top)){
			if(top != *sym){
				return false;
			}
			Stack.pop_back();
			sym++;
		}
		else if (grammar->IsVariable(top)){
			int m = std::find(Variables.begin(),Variables.end(),top) - Variables.begin();
			int n = std::find(Terminals.begin(),Terminals.end(),*sym) - Terminals.begin();
			word rule = table.at(m).at(n);
			word toCheck={error};
			if (rule == toCheck){
				return false;
			}
			else{
				Stack.pop_back();
				for(auto i = rule.rbegin(); i < rule.rend(); i++){
					Stack.push_back(*i);
				}
			}
		}
		else{
			return false;
		}
	}
	if(toParse.empty()){
		return false;
	}
	return true;
}