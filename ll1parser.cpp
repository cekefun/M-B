#include "ll1parser.h"
#include <algorithm>
#include <sstream>

LL1Parser::LL1Parser(){
	grammar = new Grammar();
	_error = "ERROR";
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

	_error = "ERROR";
	if (std::find(Terminals.begin(),Terminals.end(),_error)!=Terminals.end() and std::find(Variables.begin(),Variables.end(),_error)!=Variables.end()){
		for (int i = 1; i>0; i++){
			std::stringstream ss;
			ss<<"ERROR"<<i;
			_error = ss.str();
			if (std::find(Terminals.begin(),Terminals.end(),_error)==Terminals.end() and std::find(Variables.begin(),Variables.end(),_error)!=Variables.end()){
				break;
			}
		}
	}
	CreateTable();
	return true;
}

bool LL1Parser::CreateTable(){
	this->CreateFirstTable();
	this->CreateSecondTable();
	table = {};
	auto t = Terminals;
	t.push_back(EOS);
	for(auto m = Variables.begin(); m< Variables.end(); m++){
		table.push_back({});
		for (auto n = t.begin(); n != t.end(); n++){
			word solution = {_error};
			auto possibleRules = grammar->GetRules()[*m];
			for(auto rule = possibleRules.begin(); rule != possibleRules.end(); rule ++){
				if(secondTable[*m].find(*n) != secondTable[*m].end()){
					bool succes = true;
					for(auto a = rule->begin(); a != rule->end(); a++){
						if(firstTable[*a].find("") == firstTable[*a].end()){
							succes = false;
						}
					}
					if(succes){
						solution = {};
					}
				}

				if(rule->empty()){
					continue;
				}
				if(firstTable[rule->front()].find(*n) != firstTable[rule->front()].end() or rule->front() == *n){
					solution = *rule;
				}

			}
			table.back().push_back(solution);
		}
	}


	return true;
}

void LL1Parser::CreateFirstTable(){
	std::vector<symbol> variables = grammar->GetVariables();
	bool replaced = false;
	auto rules = grammar->GetRules();
	do{
		replaced = false;
		for(auto i = variables.begin(); i < variables.end();i++){
			auto rulesi = rules.at(*i);
			for(auto j = rulesi.begin(); j < rulesi.end(); j++){

				if(j->empty()){
					if(firstTable[*i].find("")== firstTable[*i].end()){
						firstTable[*i].insert("");
						replaced = true;
					}
					continue;
				}
				else if(grammar->IsTerminal(j->front())){
					if(firstTable[*i].find(j->front())== firstTable[*i].end()){
						firstTable[*i].insert(j->front());
						replaced = true;
					}
				}
				else{
					bool nextCharacter = false;
					for(auto k = j->begin(); k < j->end(); k++){
						if(grammar->IsTerminal(*k)){
							break;
						}
						for(auto l = firstTable[*k].begin(); l != firstTable[*k].end(); l++){
							if(l->empty()){
								nextCharacter = true;
							}
							else{
								if(firstTable[*i].find(*l)== firstTable[*i].end()){
									firstTable[*i].insert(*l);
									replaced = true;
								}
							}
						}
						if(!nextCharacter){
							break;
						}
					}
				}
			}
		}
	}while(replaced);
}

void LL1Parser::CreateSecondTable(){

	std::vector<symbol> variables = grammar->GetVariables();
	auto rules = grammar->GetRules();
	secondTable[grammar->GetStart()].insert(EOS);

	bool replaced = false;
	do{
		replaced = false;
		for(auto i = rules.begin(); i != rules.end(); i++){
			for(auto j = i->second.begin(); j != i->second.end(); j++){
				for(auto k = j->begin(); k< j->end(); k++){
					if(grammar->IsTerminal(*k)){
						continue;
					}
					if(k == j->end()-1){
						auto toAddEps = secondTable[i->first];
						for(auto m = toAddEps.begin(); m != toAddEps.end(); m++){
							if(secondTable[*k].find(*m)== secondTable[*k].end()){
								secondTable[*k].insert(*m);
								replaced = true;
							}
						}
						continue;
					}
					if(grammar->IsTerminal(*(k+1))){
						if(secondTable[*k].find(*(k+1))== secondTable[*k].end()){
							secondTable[*k].insert(*(k+1));
							replaced = true;
						}
					}

					if(grammar->IsVariable(*(k+1))){
						auto toAdd = firstTable[*(k+1)];
						for (auto l = toAdd.begin(); l != toAdd.end(); l++){
							if(l->empty()){
								bool nextVariable = false;
								for(auto f = k+1; f != j->end(); f++){
									nextVariable = false;
									for(auto t = firstTable[*f].begin(); t != firstTable[*f].end(); t++){
										if(t->empty()){
											nextVariable = true;
										}

										else{
											if(secondTable[*k].find(*t)== secondTable[*k].end()){
												secondTable[*k].insert(*t);
												replaced = true;
											}
										}

									}

									if(!nextVariable){
										break;
									}

								}
								if(nextVariable){
									for(auto f = secondTable[i->first].begin(); f != secondTable[i->first].end(); f++){
										if(secondTable[*k].find(*f)== secondTable[*k].end()){
											secondTable[*k].insert(*f);
											replaced = true;
										}
									}
								}
							}
							else if(secondTable[*k].find(*l)== secondTable[*k].end()){
								secondTable[*k].insert(*l);
								replaced = true;
							}

						}
					}
				}
			}
		}
	}while(replaced);
}

bool LL1Parser::Print(std::ostream &out){
	out << "\t|";
	for (unsigned int i = 0; i < Terminals.size();i++){
		out<< Terminals.at(i)<<"\t | ";
	}
	out << EOS<<std::endl;
	for (unsigned int i = 0; i < Variables.size(); i++){
		out << Variables.at(i)<<"\t | ";
		for(unsigned int j = 0; j < Terminals.size(); j++){
			word rule = table.at(i).at(j);
			if(rule.empty()){
				out<<'\t';
			}
			for(auto x = rule.begin(); x < rule.end(); x++){
				out <<" "<<*x;
			}
			out<<" | ";

		}

		word ending = table.at(i).back();
		if (ending.empty()){
			out<<'\t';
		}
		for(auto symb = ending.begin(); symb != ending.end(); symb++){
			out<<*symb<< " ";
		}
		out<<std::endl;
	}
	return true;
}

bool LL1Parser::Parse(word toParse){
	std::vector<symbol> Stack;
	Stack.push_back(EOS);
	Stack.push_back(grammar->GetStart());
	toParse.push_back(EOS);

	word::iterator sym = toParse.begin();
	while(!Stack.empty()){
		/*
		std::cout<<"String: ";
		for(auto i = sym; i!= toParse.end(); i++){
			std::cout<<*i <<" ";
		}
		std::cout<<std::endl<<"Stack: ";
		for(auto i = Stack.begin(); i != Stack.end(); i++){
			std::cout << *i<<" ";
		}
		std::cout<<std::endl;
		*/

		if(sym == toParse.end()){
			return false;
		}
		symbol top = Stack.back();
		if(grammar->IsTerminal(top) or top == EOS){
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
			word toCheck={_error};
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
	return true;
}

word LL1Parser::epsilonable(symbol s){
	if(grammar->IsRule(s,{})){
		return {};
	}
	std::vector<word> Rules = grammar->GetRules()[s];
	std::vector<word> possibleRules = {};

	for(std::vector<word>::iterator word = Rules.begin(); word != Rules.end(); word++){
		for(word::iterator sym = word->begin(); sym != word->end(); sym++){
			if(grammar->IsTerminal(*sym) or *sym == s){
				break;
			}
			if(sym == word->end()-1){
				possibleRules.push_back(*word);
			}
		}
	}

	for(std::vector<word>::iterator word = possibleRules.begin(); word != possibleRules.end(); word++){
		for(word::iterator sym = word->begin(); sym != word->end(); sym ++){
			if(epsilonable(*sym).front() == _error){
				break;
			}
			if(sym == word->end()-1){
				return *word;
			}
		}
	}

	return {_error};
}

std::shared_ptr<ParseTree> LL1Parser::getTree(word toParse){
	std::vector<symbol> Stack;
	Stack.push_back(EOS);
	Stack.push_back(grammar->GetStart());
	toParse.push_back(EOS);
	std::shared_ptr<Node> root(new Node(grammar->GetStart()));

	word::iterator sym = toParse.begin();
	while(!Stack.empty()){
		/*
		std::cout<<"String: ";
		for(auto i = sym; i!= toParse.end(); i++){
			std::cout<<*i <<" ";
		}
		std::cout<<std::endl<<"Stack: ";
		for(auto i = Stack.begin(); i != Stack.end(); i++){
			std::cout << *i<<" ";
		}
		std::cout<<std::endl;
		*/

		if(sym == toParse.end()){
			return std::shared_ptr<ParseTree>(new ParseTree(root));
		}
		symbol top = Stack.back();
		if(grammar->IsTerminal(top) or top == EOS){
			if(top != *sym){
				return std::shared_ptr<ParseTree>(new ParseTree(root));
			}
			Stack.pop_back();
			sym++;
		}
		else if (grammar->IsVariable(top)){
			int m = std::find(Variables.begin(),Variables.end(),top) - Variables.begin();
			int n = std::find(Terminals.begin(),Terminals.end(),*sym) - Terminals.begin();
			word rule = table.at(m).at(n);
			word toCheck={_error};
			if (rule == toCheck){
				return std::shared_ptr<ParseTree>(new ParseTree(root));;
			}
			else{
				Stack.pop_back();
				std::shared_ptr<Node> parent = getNext(top,root);
				if(rule.empty()){
					std::shared_ptr<Node> child(new Node(""));
					parent->add_child(child);
				}
				for(auto i = rule.begin(); i< rule.end(); i++){
					std::shared_ptr<Node> child(new Node(*i));
					parent->add_child(child);
				}

				for(auto i = rule.rbegin(); i < rule.rend(); i++){
					Stack.push_back(*i);
				}
			}
		}
		else{
			return std::shared_ptr<ParseTree>(new ParseTree(root));;
		}
	}
	return std::shared_ptr<ParseTree>(new ParseTree(root));

}

std::shared_ptr<Node> LL1Parser::getNext(symbol next,std::shared_ptr<Node> currentNode){
	if(currentNode->get_children().empty()){
		if(currentNode->get_info() == next){
			return currentNode;
		}
		else{
			return std::shared_ptr<Node>(nullptr);
		}
	}
	std::list<std::shared_ptr<Node>> children = currentNode->get_children();
	for(auto i = children.begin(); i!= children.end(); i++){
		std::shared_ptr<Node> child= getNext(next,*i);
		if(child.get() != nullptr){
			return child;
		}
	}
	return std::shared_ptr<Node>(nullptr);
}
