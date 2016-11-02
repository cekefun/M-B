/*
 * main.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: cedric
 */

#include "Grammar.h"
#include "ll1parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]){
	Grammar g;
	if(argc < 1){
		g.ParseGrammar("test.json");
	}
	else{
		g.ParseGrammar(argv[1]);
	}
	g.print(std::cout);
	LL1Parser p = LL1Parser(&g);
	p.Print(std::cout);
	word test;
	if(argc < 2){
		test = {"foo","bar"};
	}
	else{
		std::ifstream myFile;
		myFile.open(argv[2]);
		if(!myFile.is_open()){
			return 0;
		}
		std::string input;
		myFile >> input;
		symbol sym;
		for(auto i = input.begin(); i < input.end(); i++){
			if(*i == '|'){
				test.push_back(sym);
				sym.clear();
			}
			else{
				sym.push_back(*i);
			}
		}
		test.push_back(sym);
		
	}
	std::cout<<p.Parse(test)<<std::endl;
	return 0;
}


