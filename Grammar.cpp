/*
 * Grammar.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: cedric
 */

#include "Grammar.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using symbol = std::string;
using word = std::vector<symbol>;

Grammar::Grammar():Start{NULL} {

}

bool Grammar::IsVariable(symbol sym){
	return Variables.find(sym) != Variables.end();
}

bool Grammar::IsTerminal(symbol sym){
	return Variables.find(sym) != Terminals.end();
}

bool Grammar::IsRule(symbol header, word body){
	return Rules[header].find(body) != Rules[header].end();
}

bool Grammar::AddVariable(symbol sym){
	if(IsTerminal(sym)){
		return false;
	}
	Variables.insert(sym);
	return true;
}

bool Grammar::AddTerminal(symbol sym){
	if(IsVariable(sym)){
		return false;
	}
	Terminals.insert(sym);
	return true;
}

bool Grammar::AddRule(symbol header, word body) {
	if(!IsVariable(header)){
		return false;
	}
	for(auto i=body.begin();i!=body.end();i++){
		if(!IsVariable(*i) && !IsTerminal(*i)){
			return false;
		}
	}
	Rules[header].insert(body);
	return true;
}

void Grammar::DeleteVariable(symbol sym){
	Variables.erase(sym);
}

void Grammar::DeleteTerminal(symbol sym){
	Terminals.erase(sym);
}

void Grammar::DeleteRule(symbol header, word body){
	Rules[header].erase(body);
}

std::set<symbol> Grammar::GetVariables(){
	return Variables;
}

std::set<symbol> Grammar::GetTerminals(){
	return Terminals;
}

std::map<symbol,std::set<word> > Grammar::GetRules(){
	return Rules;
}

symbol Grammar::GetStart(){
	return Start;
}

bool Grammar::SetStart(symbol sym){
	if(!IsVariable(sym)){
		return false;
	}
	Start = sym;
	return true;
}

bool Grammar::ParseGrammar(std::string filename){
	boost::property_tree::ptree parsetree;
	boost::property_tree::read_json(filename,parsetree);
	bool succes = true;
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, parsetree.get_child("Grammar.Variables")){
		bool added = AddVariable(v.second.data());
		if(added == false){
			succes = false;
		}
	}

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, parsetree.get_child("Grammar.Terminals")){
		bool added = AddTerminal(v.second.data());
		if(added == false){
			succes = false;
		}
	}

	for (auto i = Variables.begin();i != Variables.end(); i++){
		symbol Test = *i;
		std::string path = "Grammar.Rules.";
		path += *i;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, parsetree.get_child(path)){
			word body;
			std::string parsed = v.second.data();
			std::string Symbol;
			for(auto j = parsed.begin(); j != parsed.end(); j++){
				if (*j != '|'){
					char foo = *j;
					Symbol.push_back(foo);
					continue;
				}
				body.push_back(Symbol);
				Symbol.clear();
				continue;
			}
			bool added = AddRule(Test , body);
			if(added == false){
				succes = false;
			}
		}
	}

	bool added = SetStart(parsetree.get_child("Grammar.Start").data());
	if(added == false){
		succes = false;
	}

	return succes;
}

bool Grammar::SaveGrammar(std::string filename){
	boost::property_tree::ptree root;
	boost::property_tree::ptree GrammarTree;
	boost::property_tree::ptree VariablesTree;
	boost::property_tree::ptree TerminalsTree;
	boost::property_tree::ptree RuleTrees;

	for (auto i=Variables.begin(); i!=Variables.end(); i++){
		boost::property_tree::ptree temp;
		temp.put("",*i);
		VariablesTree.push_back(std::make_pair("",temp));
	}
	for (auto i=Terminals.begin(); i!=Terminals.end(); i++){
		boost::property_tree::ptree temp;
		temp.put("",*i);
		TerminalsTree.push_back(std::make_pair("",temp));
	}
	for (auto i=Rules.begin(); i != Rules.end(); i++){
		boost::property_tree::ptree headtree;
		for (auto j=i->second.begin(); j!=i->second.end(); j++){
			boost::property_tree::ptree bodytree;
			std::string body = "";
			for (auto k = j->begin(); k!= j->end(); k++){
				if (k != j->begin()){
					body.push_back('|');
				}
				body += *k;
			}
			bodytree.put("",body);
			headtree.push_back(std::make_pair("",bodytree));
		}
		std::string foo = "";
		foo += i->first;
		RuleTrees.add_child(foo,headtree);
	}

	GrammarTree.add_child("Variables",VariablesTree);
	GrammarTree.add_child("Terminals",TerminalsTree);
	GrammarTree.add_child("Rules",RuleTrees);

	std::string foo = "";
	foo += GetStart();
	GrammarTree.put("Start",foo);

	root.add_child("Grammar",GrammarTree);
	boost::property_tree::write_json(filename,root);
	return true;
}

/*
inline std::ostream& operator<<(std::ostream& ostr,const Grammar& g){
	ostr<<"Start:"<<std::endl<<Start<<std::endl;

	ostr<<"Variables:"<<std::endl;
	for(auto i = Variables.begin(); i!=Variables.end(); i++){
		if (i != Variables.begin()){
			ostr<<", ";
		}
		ostr<<*i;
	}
	ostr<<std::endl;

	ostr<<"Terminals:"<<std::endl;
	for(auto i = Terminals.begin(); i!=Terminals.end(); i++){
		if (i != Terminals.begin()){
			ostr<<", ";
		}
		ostr<<*i;
	}
	ostr<<std::endl;

	ostr<<"Rules:"<<std::endl;
	for(auto i = Rules.begin(); i!= Rules.end(); i++){
		for(auto j = i->second.begin(); j!= i->second.end(); j++){
			ostr<<i->first<<" -> "<<*j<<std::endl;
		}
	}
	return ostr;
}
*/

void Grammar::print(std::ostream &ostr){
	ostr<<"Start:"<<std::endl<<Start<<std::endl;

	ostr<<"Variables:"<<std::endl;
	for(auto i = Variables.begin(); i!=Variables.end(); i++){
		if (i != Variables.begin()){
			ostr<<", ";
		}
		ostr<<*i;
	}
	ostr<<std::endl;
	ostr<<"Terminals:"<<std::endl;
	for(auto i = Terminals.begin(); i!=Terminals.end(); i++){
		if (i != Terminals.begin()){
			ostr<<", ";
		}
		ostr<<*i;
	}
	ostr<<std::endl;
	ostr<<"Rules:"<<std::endl;
	for(auto i = Rules.begin(); i!= Rules.end(); i++){
		for(auto j = i->second.begin(); j!= i->second.end(); j++){
			ostr<<i->first<<" -> "<<*j<<std::endl;
		}
	}
}




