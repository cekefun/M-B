#include "Grammar.h"

#include <iostream>
#include <vector>

class LL1Parser{
	public:
		LL1Parser();
		/*
		Standard constructor.
		Sets grammar to a new standard grammar, error to "ERROR" and EOS to "EOS"
		*/
		LL1Parser(Grammar*);
		/*
		Constructor with grammar as input.
		grammar is set to the input.
		error is set to "ERROR" if that is not taken. 
		If it is taken, it will use "ERRORi" with i the lowest integer <= 1 so "ERRORi" is not in the grammar
		EOS is set to "EOS" if that is not taken.
		If it is taken, it will use "EOS" with i the lowest integer <= 1 so "EOS" is not in the grammar
		*/
		bool setGrammar(Grammar*);
		/*
		Sets grammar to input and recalculates ERROR and EOS. (see LL1Parser(Grammar*))
		*/
		bool Print(std::ostream&);
		/*
		Prints the ll(1) table to the ostream
		*/
		bool Parse(word);
		/*
		Checks wether the word is part of the grammar or not.
		*/

	private:
		bool CreateTable();
		Grammar *grammar;
		symbol error;
		symbol EOS;
		std::vector<symbol> Variables;
		std::vector<symbol> Terminals;
		std::vector<std::vector<word>> table;


};