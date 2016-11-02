#include "Grammar.h"

#include <iostream>
#include <vector>

class LL1Parser{
	public:
		LL1Parser();
		LL1Parser(Grammar*);
		bool setGrammar(Grammar*);
		bool Print(std::ostream&);
		bool Parse(word);
	private:
		bool CreateTable();
		Grammar *grammar;
		symbol error;
		symbol EOS;
		std::vector<symbol> Variables;
		std::vector<symbol> Terminals;
		std::vector<std::vector<word>> table;


};