/*
 * CYK.h
 *
 *  Created on: Nov 3, 2016
 *  Author: Robbe Heirman
 *  CYK.h contains the CYK class wich will act as a functor to implement
 *  the CYK algorithm. CYK tests if a string is part of a (CNF) grammar.
 */


#ifndef GRAMMAR_CYK_H_
#define GRAMMAR_CYK_H_

#include "Grammar.h"
#include "ParseTree.h"

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <memory>

using namespace std;


class CYK {
/*
 * The CYK algorithm. Will act as a functor since it is just a fucntion
 * that evaluates if a string is in a language of a grammar. But functors
 * give us additional features to remember lists of the constructed table.
 * this way we can produce step-wise output.
 */
public:
	CYK();
	// Default constructor.

	virtual ~CYK();
	// Default destructor

	bool operator()(string strng, Grammar& grammar) ;
	/*
	 * We overload the () operator. THis way we can call CYK as a function.
	 * Parameter: strng: a string to be evaluated. grammar: the grammar we
	 * are going to evaluate our string in.
	 * Returns true if the string is part of the language of the grammar.
	 * Returns false if not.
	 */

	void print_table();

	vector<ParseTree> get_parseTrees(Grammar& gram);

private:

	map<string,vector<string>> reverse_dic(Grammar& grammar) const;
	vector<vector<string>> basis(string& str, Grammar& g);
	vector<string> calc_X(Grammar& g, int i, int j);
	void print_nodes();

	vector<vector<vector<string>>> table;
	vector <vector <vector <std::shared_ptr<Node>>>> tree_table;

};

#endif /* GRAMMAR_CYK_H_ */
