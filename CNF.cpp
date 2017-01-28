//
// Created by Kristof Buts on 1/19/17.
//

#include "Grammar.h"
#include "Utilities/Utilities.h"

#include <algorithm>
#include <iostream>

void Grammar::convertToCNF() {
//	std::cout << "Converting Grammar to CNF" << std::endl;

//	std::cout << "*** STEP 0 ***" << std::endl;
	eliminateUselessVars();

//	std::cout << "*** STEP 1 ***" << std::endl;
	// step 1
	// if start symbol S occurs on some right side, make new start symbol S' and a new production S' -> S

	/*
	// check if start symbol occurs on right side
	bool found = findStartSymbolInProductions();
	if (found) {
		this->AddVariable("S0"); // new start symbol
		std::vector<symbol> *p = new std::vector<symbol>; // temporary to make word
		p->push_back(this->Start);
		this->AddRule("S0", *p);
		this->SetStart("S0");
		delete p; // free up resources
	}
	*/

//	std::cout << "*** STEP 2 ***" << std::endl;
	removeNullProductions();

//	std::cout << "*** STEP 3 ***" << std::endl;
	removeUnitProductions();

//	std::cout << "*** STEP 4 ***" << std::endl;
	removeLongBodies();

//	std::cout << "*** STEP 5 ***" << std::endl;
	removeMixedBodies();
}

void Grammar::eliminateUselessVars() {
	eliminateNonGenerating();
	eliminateNonReachable();
}

void Grammar::eliminateNonGenerating() {
	std::set<symbol> generating;
	bool newfound;
	do {
		newfound = false;
		for (auto r: Rules) {
			if ( std::find(generating.begin(), generating.end(), r.first) != generating.end() ) {
				continue;
			}
			for (auto w: r.second) {
				// if w is a terminal string or all vars in w are generating, then symbol is generating
				bool gen = true;
				for (auto it: w) {
					// loop over each symbol

					bool isTerm = this->IsTerminal(it);
					bool isGen = std::find(generating.begin(), generating.end(), it) != generating.end();
					if (!(isTerm or isGen)) {
						gen = false;
						break;
					}
				}
				if (gen) {
					generating.insert(r.first);
					newfound = true;
				}
			}
		}
	} while ( newfound );

	/*
	std::cout << "Generating symbols: ";
	for (auto it: generating) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
	*/

	std::vector<symbol> vars = this->GetVariables();
	std::set<symbol> varset(vars.begin(), vars.end());

	std::set<symbol> nongen;
	std::set_difference( varset.begin(), varset.end(), generating.begin(), generating.end(), \
		std::inserter(nongen, nongen.begin()));

	for (symbol v: nongen) {
		// eliminate each symbol
		for (auto r: Rules) {
			std::set<word> rulestodelete;
			for (auto w: r.second) {
				if ( std::find(w.begin(), w.end(), v ) != w.end() ) {
					rulestodelete.insert(w);
					continue;
				}
			}
			for (auto it: rulestodelete) {
				this->DeleteRule(r.first, it);
			}
		}
		this->Rules.erase(v);
		if ( IsTerminal(v) ) {
			this->DeleteTerminal(v);
		} else if ( IsVariable(v) ) {
			this->DeleteVariable(v);
		}
	}
}

void Grammar::eliminateNonReachable() {
	std::set<symbol> reachable;
	reachable.insert( this->GetStart() );

	bool newfound;
	do {
		newfound = false;
		std::set<symbol> tempreach = reachable;
		for (auto r: reachable) {
			if (IsVariable(r)) {
				for ( auto i: Rules[r] ) {
					for ( auto j: i) {
						if ( tempreach.find(j) == tempreach.end() ) {
							newfound = true;
							tempreach.insert(j);
						}
					}
				}
			}
		}
		reachable = tempreach;
	} while ( newfound );

	/*
	std::cout << "Reachable symbols: ";
	for (auto it: reachable) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
	*/

	// eliminate nonreachable symbols

	std::vector<symbol> vars = this->GetVariables();
	std::set<symbol> symbolset = std::set<symbol>(vars.begin(), vars.end());
	std::vector<symbol> terms = this->GetTerminals();
	std::set<symbol> termset = std::set<symbol>(terms.begin(), terms.end());
	symbolset.insert(termset.begin(), termset.end());
	std::set<symbol> nonreach;
	std::set_difference( symbolset.begin(), symbolset.end(), reachable.begin(), reachable.end(), \
		std::inserter(nonreach, nonreach.begin()));

	/*
	std::cout << "Non-Reachable symbols: ";
	for (auto it: nonreach) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
	*/

	// eliminate nongenerating symbols

	for (symbol v: nonreach) {
		// eliminate each symbol
		for (auto r: Rules) {
			std::set<word> rulestodelete;
			for (auto w: r.second) {
				if ( std::find(w.begin(), w.end(), v ) != w.end() ) {
					rulestodelete.insert(w);
				}
			}
			for (auto it: rulestodelete) {
				this->DeleteRule(r.first, it);
			}
		}
		this->Rules.erase(v);
		if ( IsTerminal(v) ) {
			this->DeleteTerminal(v);
		} else if ( IsVariable(v) ) {
			this->DeleteVariable(v);
		}
	}
}

void Grammar::removeNullProductions() {
	// removal of null productions in CFG
	// a non-terminal A is nullable if:
	// 		there exists a production A -> [epsilon]
	// 			or
	// 		there exists a derivation A -> ... -> [epsilon]

	// removal procedure:
	// step 1
	// 		find all nullable non-terminals in the CFG
	// step 2
	// 		for each A -> a construct a new production A -> x
	// 		where x = a - (one or more nullables in a)
	// step 3
	// 		combine the original productions with the new ones from step 2
	// 		and remove epsilon productions

	// once we have nullables, add additional rules and remove A -> [epsilon] for any A

	// step 1
//	std::cout << "Find nullable non-terminals in CFG" << std::endl;
	std::vector<symbol> nullables = this->findNullables();

	// step 2
	// if A -> X1X2...Xn
	// add all productions that can be formed by eliminating some or all of those Xi's that are nullable
	// BUT if all Xi's are nullable -> don't add the case where they are all deleted
	for (std::pair<symbol, std::vector<word>> r: Rules) {
		// per symbol, loop over each rule
		for (word w: r.second) {
			// check which of the symbols in the word are nullable
			// and add their indexes to a vector
			std::vector<int> nullableindexes;
//			for (symbol s: w) {
			for (int i = 0; i < w.size(); ++i) {
				if ( std::find( nullables.begin(), nullables.end(), w.at(i) ) != nullables.end() ) {
					nullableindexes.push_back(i);
				}
			}

			std::vector< std::vector<int> > pwrset;
			Utilities::powerset(nullableindexes, pwrset); // get powerset of indexes

			if ( w.size() == nullableindexes.size() ) {
				// skip the case where we end up with [epsilon] (happens if all symbols in rule are nullable
				pwrset.erase(pwrset.begin());
			}

			for ( std::vector<int> it: pwrset ) {
				if ( it.size() != nullableindexes.size() ) {
					// if condition is true, it's the original rule

					word temp;
					for (int i = 0; i < w.size(); ++i) {
						// loop over original rule and check if the current symbol is nullable
						if ( std::find(nullableindexes.begin(), nullableindexes.end(), i) == nullableindexes.end() ) {
							// if current symbol is not nullable, add it
							temp.push_back( w.at(i) );
						} else {
							if ( std::find(it.begin(), it.end(), i) != it.end()) {
								// if current symbol is nullable and in the subset we're composing, add it
								temp.push_back( w.at(i) );
							}
						}
					}

					// add new rule to CFG
					this->AddRule(r.first, temp);

				}
			}
		}
	}

	// step 3
	// remove clean nullables

	for (std::pair<symbol, std::vector<word>> it: Rules) {
		// per symbol
		for (word it2: it.second) {
			if (it2.size() == 1) {
				if (it2.at(0) == "") {
					// delete rule
					this->DeleteRule(it.first, it2);
				}
			}
		}
	}
}

std::vector<symbol> Grammar::findNullables() {
	std::vector<symbol> nullables;

	// first try to find clean nullables
	// ie vars that have explicit productions A -> [epsilon]
	for (std::pair<symbol, std::vector<word>> it: Rules) {
		// per symbol
		for (word it2: it.second) {
			if (it2.size() == 1) {
				if (it2.at(0) == "") {
					nullables.push_back(it.first);
				}
			}
		}
	}

	// loop over variables that are not in nullables already
	// if a new nullable is found, add it to the vector and start over
	bool pass = false;
	while (!pass) {
		bool foundnew = false;
		for ( symbol v: this->GetVariables() ) {
			if ( std::find(nullables.begin(), nullables.end(), v) != nullables.end() ) {
				// if we found var is nullable already, skip
				continue;
			}

			bool foundnullablerule = false;
			// loop over all rules for this symbol
			// if we find a rule with only nullable symbols -> add symbol to nullables and start over
			for (word r: Rules[v]) {

				bool allsymbolsnullable = true; //
				for (symbol i: r) {
					if ( std::find(nullables.begin(), nullables.end(), i) == nullables.end() ) {
						allsymbolsnullable = false;
					}
				}

				if (allsymbolsnullable) {
					// if all symbols in the rule are nullable, the rule is nullable
					foundnullablerule = true;
					break; // stop checking rules of this var, it's nullable either way
				}
			}

			if (foundnullablerule) {
				foundnew = true;
				nullables.push_back(v);
			}
		}

		if (!foundnew) {
			pass = true; // if no new nullables are found anymore, we can stop looping
		}
	}

	/*
	std::cout << "Following nullables are found: ";
	for (auto it: nullables) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
	*/

	return nullables;
}

void Grammar::removeUnitProductions() {
	// Any production in the form A -> B with A and B nonterms are unit production

	// removal procedure
	// step 1
	// 		add prod A -> x whenever B -> x
	//		x is a terminal, can be [epsilon]
	// step 2
	// 		remove A -> B
	// step 3
	// 		repeat from step 1 until all unit prods are removed

	// check if there are unit productions
	std::map<symbol, symbol> unitprods = findUnitProductions();

	/*
	// print out unit production for debug
	std::cout << "unit productions found: " << std::endl;
	if (unitprods.size() > 0) {
		for (auto r: unitprods) {
			for (auto w: r.second) {
				std::cout << r.first << " -> " << w << std::endl;
			}
		}
	}
	*/

	while(unitprods.size() > 0) {

		for(auto up: unitprods) {
			if ( up.first == up.second ) {
				this->DeleteRule(up.first, std::vector<symbol>{up.second});
				break;
			}
			for (auto it: Rules[up.second]) {
				if (it.size() == 1 and IsTerminal(it.at(0))) {
					this->AddRule(up.first, it);
					this->DeleteRule(up.first, std::vector<symbol>{up.second});
				} else if ( it.size() > 1 ) {
					this->AddRule(up.first, it);
					this->DeleteRule(up.first, std::vector<symbol>{up.second});
				}
			}
		}


		unitprods = findUnitProductions(); // renew to see if we can exit while loop
	}

}

std::map<symbol, symbol> Grammar::findUnitProductions() {
	// return is <symbol, symbol> -> rhs is always only one symbol
	std::map<symbol, symbol> ret;
	for (std::pair<symbol, std::vector<word>> r: Rules) {
		for (word w: r.second) {
			if (w.size() == 1) {
				if (this->IsVariable(w.at(0))) {
					ret.insert(std::make_pair(r.first, w.at(0)));
				}
			}
		}
	}
	return ret;
}

std::map<word, std::vector<symbol>> Grammar::findLongBodies() {
	std::map<word, std::vector<symbol>> longbodies; // REVERSED
	// this map goes from the RHS to the LHS so productions with the same left hand side get grouped
	// this way we can change them al together
	for (auto r: Rules) {
		// loop over each symbol
		for (word w: r.second) {
			// loop over each rule on current symbol
			if ( w.size() > 2 ) {
				// body's gonna get split
//				std::cout << r.first << " -> ";
//				for (auto it: w ) {
//					std::cout << it;
//				}
//				std::cout << std::endl;
				longbodies[w].push_back(r.first);
			}
		}
	}
	return longbodies;
}

void Grammar::removeLongBodies() {
	int ctr = 0; // for indexing added states
	std::map<word, std::vector<symbol>> longbodies = findLongBodies(); // REVERSED
	// this map goes from the RHS to the LHS so productions with the same left hand side get grouped
	// this way we can change them al together

	while ( longbodies.size() > 0 ) {
		// map contains per word that is too long the variables that share it
		for ( auto lb: longbodies ) {
			// we loop over every symbol that is too long, e.g. ASA

			/*
			// print out for debug
			std::cout << "eliminating ";
			for (auto it: lb.first) {
				std::cout << it;
			}
			std::cout << std::endl;
			*/

			word first{lb.first.front()};
			word rest(lb.first.begin() + 1, lb.first.end());

			symbol newstate = "X" + std::to_string(ctr);
			++ctr;

			this->AddVariable(newstate);
			this->AddRule(newstate, rest);
			word newprod = {first.front(), newstate};
			for (auto it: lb.second) {
				// add new transition to each symbol that has the original one
				this->AddRule(it, newprod);
				this->DeleteRule(it, lb.first);
			}
		}

		longbodies = findLongBodies(); // renew to see if we need to repeat
	}

}

void Grammar::removeMixedBodies() {
	/*
	 * If the right side of any production is in the form A → aB where a is a terminal and A, B are non-terminal,
	 * then the production is replaced by A → XB and X → a.
	 * Repeat this step for every production which is in the form A → aB.
	 */
	// process fairly similar to previous step
	int ctr = 0; // for indexing added states
//	std::map<word, std::vector<symbol>> mixedbodies = findMixedBodies(); // REVERSED
	std::set<symbol> mixedbodies = findMixedBodies();

	for ( auto mb: mixedbodies ) {
		// we loop over every symbol that is mixed, e.g. aB

		/*
		// print out for debug
		std::cout << "eliminating " << mb << std::endl;
		*/

		// we make a new state Ynn and add a single transition Ynn -> mb
		// then we loop through all productions and replace every occurence of mb with Ynn

		word term{mb};

		symbol newstate = "Y" + std::to_string(ctr);
		++ctr;

		this->AddVariable(newstate);

		for (std::pair<symbol, std::vector<word>> r: Rules) {
			for (word w: r.second) {
				if (w.size() == 1) {
					continue;
				}
				// loop through each word symbol by symbol
				// and replace every occurence of mb with newstate
				word t;
				for (int i = 0; i < w.size(); ++i) {
					if (w.at(i) == mb) {
						t.push_back(newstate);
					} else {
						t.push_back(w.at(i));
					}
				}
				this->DeleteRule(r.first, w);
				this->AddRule(r.first, t);
			}
		}

		// add rule after to avoid it getting deleted by the previous loop
		this->AddRule(newstate, term);
	}
}

std::set<symbol> Grammar::findMixedBodies() {
	std::set<symbol> ret;

	// find all terminals that appear in production with size > 2
	for (auto r: Rules) {
		// loop over each symbol
		for (word w: r.second) {
			// loop over each rule on current symbol
			if (w.size() >= 2) {
				for (auto s: w) {
					if (IsTerminal(s)) {
						ret.insert(s);
					}
				}
			}
		}
	}

	return ret;
}
