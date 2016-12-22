/*
 * main.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: cedric
 */

#include "Grammar.h"
#include "ll1parser.h"
#include "CYK.h"
#include "ParseTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

int main(int argc, char *argv[]){

	Grammar gram;


	if(argc < 2){
		gram.ParseGrammar("CNF.json");
	}

	else{
		gram.ParseGrammar(argv[1]);
	}
	gram.SaveGrammar("Test.json");
	CYK alg;
	string reader;
	while(true){
		cout << "Waiting for input:" << endl;
		cin >> reader;
		if(reader == "-quit"){
			cout <<"Terminated" <<endl;
			return 0;
		}
		else if(reader == "-print"){
			gram.print(std::cout);
		}
		else{

			if(alg(reader,gram)){
				alg.print_table();
				ParseTree tree = alg.get_parseTrees(gram)[0];
				tree.to_dot("tree.dot");
				std::system("dot -Tpng -O tree.dot");
				std::system("xdg-open tree.dot.png");

				cout << reader << " is in Grammar" << endl;
			}
			else{
				alg.print_table();
				cout << reader << " is not in Grammar" << endl;
			}
		}
	}
	return 0;
}


