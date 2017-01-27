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

using namespace std;

Grammar::Grammar():Start{NULL} {

}

bool Grammar::IsVariable(symbol sym){
	return std::find(Variables.begin(),Variables.end(),sym) != Variables.end();
}

bool Grammar::IsTerminal(symbol sym){
	return std::find(Terminals.begin(),Terminals.end(),sym) != Terminals.end();
}

bool Grammar::IsRule(symbol header, word body){
	return std::find(Rules[header].begin(),Rules[header].end(),body) != Rules[header].end();
}

bool Grammar::AddVariable(symbol sym){
	if(IsTerminal(sym)){
		return false;
	}
	Variables.push_back(sym);
	return true;
}

bool Grammar::AddTerminal(symbol sym){
	if(IsVariable(sym)){
		return false;
	}
	Terminals.push_back(sym);
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
	Rules[header].push_back(body);
	return true;
}

void Grammar::DeleteVariable(symbol sym){
	auto found = std::find(Variables.begin(),Variables.end(),sym);
	if (found != Variables.end()){
		Variables.erase(found);
	}
}

void Grammar::DeleteTerminal(symbol sym){
	auto found = std::find(Terminals.begin(),Terminals.end(),sym);
	if (found != Terminals.end()){
		Terminals.erase(found);
	}
}

void Grammar::DeleteRule(symbol header, word body){
	auto found = std::find(Rules[header].begin(),Rules[header].end(),body);
	if (found != Rules[header].end()){
		Rules[header].erase(found);
	}
}

std::vector<symbol> Grammar::GetVariables(){
	return Variables;
}

std::vector<symbol> Grammar::GetTerminals(){
	return Terminals;
}
std::map<symbol,std::vector<word> > Grammar::GetRules(){
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
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, parsetree.get_child("Variables")){
		bool added = AddVariable(v.second.data());
		if(added == false){
			succes = false;
		}
	}

	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, parsetree.get_child("Terminals")){
		bool added = AddTerminal(v.second.data());
		if(added == false){
			succes = false;
		}
	}
	
	BOOST_FOREACH(auto &v, parsetree.get_child("Productions")){
		symbol head = v.second.get_child("head").data();
		word body;
		body.clear();

		BOOST_FOREACH(auto &w, v.second.get_child("body")){
			body.push_back(w.second.data());
		}

		bool added = AddRule(head , body);
		if(added == false){
			succes = false;
		}
	}
	

	bool added = SetStart(parsetree.get_child("Start").data());
	if(added == false){
		succes = false;
	}

	return succes;
}

bool Grammar::SaveGrammar(std::string filename){

	namespace pt = boost::property_tree;
	boost::property_tree::ptree root;

	pt::ptree variables;
	for(size_t i = 0; i < this->Variables.size(); i++){

		pt::ptree variable;
		variable.put("",this->Variables[i]);

		variables.push_back(std::make_pair("",variable));

	}
	root.add_child("Variables",variables);

	pt::ptree terminals;
	for(size_t i = 0; i < this->Terminals.size(); i++){

		pt::ptree terminal;
		terminal.put("",this->Terminals[i]);

		terminals.push_back(std::make_pair("",terminal));

	}
	root.add_child("Terminals",terminals);

	pt::ptree productions;
	for(auto const& ent1 : this->Rules) {

		for(size_t i = 0; i < ent1.second.size(); i++){
			pt::ptree production;
			production.put("head",ent1.first);

			pt::ptree body;
			for(size_t j = 0; j < ent1.second[i].size(); j++){
				pt::ptree bn;
				bn.put("",ent1.second[i][j]);
				body.push_back(std::make_pair("",bn));
			}
			production.add_child("body",body);

			productions.push_back(std::make_pair("",production));
		}



	}
	root.add_child("Productions",productions);
	root.put("Start",this->Start);

	pt::write_json(filename, root);
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
			ostr<<i->first<<" -> ";
			for (auto k = j->begin(); k!= j->end();k++){
				ostr<<*k;
			}
			ostr<<std::endl;
		}
	}
}




