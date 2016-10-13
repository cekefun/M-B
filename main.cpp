/*
 * main.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: cedric
 */

#include "Grammar.h"
#include <iostream>

int main(){
	Grammar g;
	g.ParseGrammar("test.json");
	g.print(std::cout);
	return 1;
}


