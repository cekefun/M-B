/*
 * Parser.cpp
 *
 *  Created on: 5-nov.-2015
 *      Author: Raphael
 */

#include "Parser.h"

Parser::Parser() {
	//does nothing
	return;
}

bool Parser::ParseGrammar(const char* DocumentName, grammar& Input){
	TiXmlDocument doc;
	bool opened = doc.LoadFile(DocumentName);
	if(!opened){
		std::cout<<doc.ErrorDesc()<<std::endl;
		return false;
	}

	TiXmlElement *root = doc.FirstChildElement();
	//Root has to exist
	if(root == NULL){
		std::cout<<"Failed to load file: No root element."<<std::endl;
		doc.Clear();
		return false;
	}

	std::string rootValue = root->Value();

	if(rootValue!= "CFG"){
		std::cout<<"Failed to load file: Wrong root element."<<std::endl;
		doc.Clear();
		return false;
	}

	grammar Output = grammar();
	std::set<std::string> Variables;
	std::set<std::string> Terminals;
	std::string Start;
	for(TiXmlElement* elem = root->FirstChildElement();
			elem != NULL; elem = elem->NextSiblingElement()){
		std::string elemName = elem->Value();
		/*
		 * Reading the Variables
		 */
		if(elemName == "Variables"){
			const char* VariablesList = elem->GetText();
			if(VariablesList == NULL){
				std::cout<<"Failed to parse file: No variables found"<<std::endl;
				doc.Clear();
				return false;
			}
			std::string VarList = VariablesList;
			std::string begin = "";
			for(std::string::iterator sym = VarList.begin();sym!= VarList.end(); sym++){
				if(*sym == '|'){
					if(begin == ""){
						std::cout<<"Failed to parse file: Empty variable not allowed."<<std::endl;
						doc.Clear();
						return false;
					}
					if(Variables.find(begin) != Variables.end()){
						std::cout<<"Failed to parse file: Double variables not allowed."
								<<std::endl;
						doc.Clear();
						return false;
					}
					Variables.insert(begin);
					begin = "";
					continue;
				}

				begin.push_back(*sym);
			}
			Variables.insert(begin);

			int amount_of_start = 0;
			const char* result;
			for(TiXmlElement* StartSymbol = elem->FirstChildElement();
					StartSymbol != NULL;StartSymbol = StartSymbol->NextSiblingElement()){
				amount_of_start++;
				std::string nameCheck = StartSymbol->Value();
				if(nameCheck != "StartSymbol"){
					std::cout<<"Failed to parse file: StartSymbol node not found."<<std::endl;
					doc.Clear();
					return false;
				}
				result = StartSymbol->GetText();
				if(result == NULL){
					std::cout<<"Failed to parse file: StartSymbol not found."<<std::endl;
					doc.Clear();
					return false;
				}
			}
			if(amount_of_start != 1){
				std::cout<<"Failed to parse file: Incorrect amount of startsymbols."<<std::endl;
				doc.Clear();
				return false;
			}
			std::string StartString = result;
			if(Variables.find(StartString) == Variables.end()){
				std::cout<<"Failed to parse file: StartSymbol is not a variable."<<std::endl;
				doc.Clear();
				return false;
			}
			Start = StartString;
			continue;
		}

		/*
		 * Reading the terminals
		 */
		if(elemName == "Terminals"){
			const char* TerminalsList = elem->GetText();
			//The terminals have to exist
			if(TerminalsList == NULL){
				std::cout<<"Failed to parse file: No terminals found"<<std::endl;
				doc.Clear();
				return false;
			}
			std::string TerList = TerminalsList;
			std::string begin = "";
			for(std::string::iterator sym = TerList.begin(); sym != TerList.end(); sym++){
				if(*sym == '|'){
					if(begin == ""){
						std::cout<<"Failed to parse file: Empty terminal not allowed."<<std::endl;
						doc.Clear();
						return false;
					}
					if(Variables.find(begin) != Variables.end()){
						std::cout<<"Failed to parse file: "
								<<"Terminal that is also a Variable is not allowed."<<std::endl;
						doc.Clear();
						return false;
					}
					Terminals.insert(begin);
					begin = "";
					continue;
				}

				begin.push_back(*sym);
			}
			Terminals.insert(begin);
			continue;
		}


		/*
		 * All the productionrules
		 */
		if(elemName == "Productions"){
			Output = grammar(Variables,Terminals,Start);
			for(TiXmlElement* rule = elem->FirstChildElement();rule != NULL;
					rule = rule->NextSiblingElement()){
				std::string NameCheck = rule->Value();
				//The value of the element has to be "Rule"
				if(NameCheck != "Rule"){
					std::cout<<"Failed to parse file: Wrong children in Productions"<<std::endl;
					doc.Clear();
					return false;
				}
				const char* LHS = rule->Attribute("LHS");
				//LHS has to exist
				if(LHS == NULL){
					std::cout<<"Failed to parse file: Rule with LHS missing"<<std::endl;
					doc.Clear();
					return false;
				}
				std::string LHSstr = LHS;
				//LHS has to be 1 character
				const char* RHS = rule->Attribute("RHS");
				//RHS has to exist
				if(RHS == NULL){
					std::cout<<"Failed to parse file: Rule with RHS missing"<<std::endl;
					doc.Clear();
					return false;
				}
				std::string RHSstr = RHS;
				std::string rulestr = "";
				std::vector<std::string> ruleList;
				for(std::string::iterator i = RHSstr.begin(); i != RHSstr.end(); i++){
					if(*i == '|'){
						ruleList.push_back(rulestr);
						rulestr = "";
						bool succes = Output.addRule(LHSstr,ruleList);
						//if the rule is not properly added, it should DIE
						if(!succes){
							std::cout<<"Failed to parse file: "
									<<"Apperently the rule was not added."<<std::endl;
							return false;
						}
						ruleList.clear();
						continue;
					}
					if(*i == ' '){
						ruleList.push_back(rulestr);
						rulestr = "";
						continue;
					}
					rulestr.push_back(*i);
				}

				ruleList.push_back(rulestr);
				bool succes = Output.addRule(LHSstr,ruleList);
				//if the rule is not properly added, it should DIE
				if(!succes){
					return false;
				}
			}
		}
		if(elemName != "Variables" && elemName != "Terminals" && elemName != "Productions"){
			std::cout<<"Failed to parse file: Wrong rootchildren.";
			doc.Clear();
			return false;
		}

	}
	if(Output.IsEmpty()){
		std::cout<<"Failed to parse file: The creation of the grammar was not allowed."<<std::endl;
		doc.Clear();
		return false;
	}
	Input = Output;
	return true;

}

bool Parser::ParsePDA(const char* DocumentName, pda &p){
    TiXmlDocument doc;
    bool opened = doc.LoadFile(DocumentName);
    if(!opened){
        std::cout<<doc.ErrorDesc()<<std::endl;
        return false;
    }

    TiXmlElement *root = doc.FirstChildElement();
    //Root has to exist
    if(root == NULL){
        std::cout<<"Failed to load file: No root element."<<std::endl;
        doc.Clear();
        return false;
    }

    std::string rootValue = root->Value();

    if(rootValue!= "PDA"){
        std::cout<<"Failed to load file: Wrong root element."<<std::endl;
        doc.Clear();
        return false;
    }

    std::set<std::string> states;
    std::set<std::string> alphabet;
    std::set<std::string> stackSymbols;
    std::vector<Transition> transitions;
    std::string startState;
    std::string startSymbol;
    std::set<std::string> finalStates;

    for(TiXmlElement* elem = root->FirstChildElement();
            elem != NULL; elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();


        if(elemName == "Type")
        {
            //As long as I don't know WTF this is, I won't do shit here...
        }
        else if(elemName == "Alphabet")
        {
            for(TiXmlElement* runner = elem->FirstChildElement();
                        runner != NULL; runner = runner->NextSiblingElement())
            {
                std::string runnerTag = runner->Value();
                if( runnerTag == "symbol" )
                {
                    std::string val;
                    if( runner->GetText() )
                        val = std::string(runner->GetText());
                    else val = "";
                    alphabet.insert(val);

                }
                else
                {
                    std::cerr << "Invalid child element '" << runnerTag
                            << "' for Alphabet." << std::endl;
                }
            }
        }
        else if(elemName == "StackAlphabet")
        {
            for(TiXmlElement* runner = elem->FirstChildElement();
                        runner != NULL; runner = runner->NextSiblingElement())
            {
                std::string runnerTag = runner->Value();
                if( runnerTag == "symbol" )
                {
                    std::string val;
                    if( runner->GetText() )
                        val = std::string(runner->GetText());
                    else val = "";
                    stackSymbols.insert(val);
                }
                else if( runnerTag == "start" )
                {
                    std::string val;
                    if( runner->GetText() )
                        val = std::string(runner->GetText());
                    else val = "";
                    if( !val.empty() )
                    {
                        stackSymbols.insert(val);
                        startSymbol = val;
                    }
                }
                else
                {
                    std::cerr << "Invalid child element '" << runnerTag
                            << "' for StackAlphabet." << std::endl;
                }
            }
        }
        else if(elemName == "States")
        {
            for(TiXmlElement* runner = elem->FirstChildElement();
                                    runner != NULL; runner = runner->NextSiblingElement())
            {
                std::string runnerTag = runner->Value();
                if( runnerTag == "start" )
                {
                    std::string val;
                    if( runner->GetText() )
                        val = std::string(runner->GetText());
                    else val = "";
                    if( !(val.empty() or (!startState.empty())) )
                    {
                        states.insert(val);
                        startState = val;
                    }
                    else
                    {
                        std::cerr << "Invalid start state defined: " << val
                                << "\nStart state may not be empty and should only "
                                << "occur once in States." << std::endl;
                    }
                }
                else if( runnerTag == "state" )
                {
                    std::string val;
                    if( runner->GetText() )
                        val = std::string(runner->GetText());
                    else val = "";
                    if( !(val.empty() or (startState == val) or
                            (finalStates.find(val) != finalStates.end())) )
                        states.insert(val);
                    else
                    {
                        std::cerr << "Invalid start state defined: " << val
                                << "\nState may not be empty, "
                                << "nor have the same value as the start state, "
                                << "nor be present in the set of accepting states." << std::endl;
                    }
                }
                else if( runnerTag == "accept" )
                {
                    std::string val;
                    if( runner->GetText() )
                        val = std::string(runner->GetText());
                    else val = "";
                    if( !(val.empty() or (states.find(val) != states.end())) )
                    {
                        states.insert(val);
                        finalStates.insert(val);
                    }
                    else
                    {
                        std::cerr << "Invalid accept state defined: " << val
                                << "\nAccept state may not be empty, "
                                << "nor be present in the set of states." << std::endl;
                    }

                }
                else
                {
                    std::cerr << "Invalid child element '" << runnerTag
                            << "' for States." << std::endl;
                }
            }
        }
        else if(elemName == "Transitions")
        {
            for(TiXmlElement* runner = elem->FirstChildElement();
                        runner != NULL; runner = runner->NextSiblingElement())
            {
                std::string runnerTag = runner->Value();
                if( runnerTag == "transition" )
                {
                    std::string state;
                    std::string inputSymbol;
                    std::string stackSymbol;
                    std::string nextState;
                    std::vector<std::string> pushSymbols;

                    for(TiXmlElement* runner2 = runner->FirstChildElement();
                            runner2 != NULL; runner2 = runner2->NextSiblingElement())
                    {
                        std::string runner2Tag = runner2->Value();
                        if( runner2Tag == "from" )
                        {
                            std::string val;
                            if( runner2->GetText() )
                                val = std::string(runner2->GetText());
                            else val = "";
                            if( !(val.empty() or (states.find(val) == states.end())) )
                            {
                                state = val;
                            }
                            else
                            {
                                std::cerr << "Invalid \"from\" state defined: " << val
                                        << "\n\"from\" state may not be empty and has "
                                        << "to be present in States." << std::endl;
                                break;
                            }
                        }
                        else if( runner2Tag == "to" )
                        {
                            std::string val;
                            if( runner2->GetText() )
                                val = std::string(runner2->GetText());
                            else val = "";
                            if( !(val.empty() or (states.find(val) == states.end())) )
                            {
                                nextState = val;
                            }
                            else
                            {
                                std::cerr << "Invalid \"to\" state defined: " << val
                                        << "\n\"to\" state may not be empty and has "
                                        << "to be present in States." << std::endl;
                                break;
                            }
                        }
                        else if( runner2Tag == "input" )
                        {
                            std::string val;
                            if( runner2->GetText() )
                                val = std::string(runner2->GetText());
                            else val = "";
                            if( val.empty() or alphabet.find(val) != alphabet.end() )
                                inputSymbol = val;
                            else
                            {
                                std::cerr << "Invalid input symbol defined: " << val
                                    << "\nInput symbol must be present in Alphabet." << std::endl;
                                break;
                            }
                        }
                        else if( runner2Tag == "stacktop" )
                        {
                            std::string val;
                            if( runner2->GetText() )
                                val = std::string(runner2->GetText());
                            else val = "";
                            if( val.empty() or stackSymbols.find(val) != stackSymbols.end() )
                                stackSymbol = val;
                            else
                            {
                                std::cerr << "Invalid stacktop defined: " << val
                                << "\nStacktop must be present in StackAlphabet." << std::endl;
                                break;
                            }
                        }
                        else if( runner2Tag == "push" )
                        {

                            std::string val;
                            if( runner2->GetText() )
                                val = std::string(runner2->GetText());
                            else val = "";
                            unsigned int lastVal=0;
                            for(std::string::size_type i = 0;
                                    i < val.length(); ++i)
                            {
                                if( val[i] == '|' )
                                {
                                    std::string symb(val.substr(lastVal, (i-lastVal)));
                                    lastVal = (i+1);
                                    if( !symb.empty() and
                                            stackSymbols.find(symb) == stackSymbols.end() )
                                    {
                                        std::cerr << "Invalid push symbol: "<< symb
                                            <<"\nA push symbol must be present in StackAlphabet."
                                            << " Skipping to next symbol..."<<std:: endl;
                                    }
                                    else pushSymbols.push_back(symb);
                                }
                            }
                            std::string symb(val.substr(lastVal));
                            if( !symb.empty() and
                                    stackSymbols.find(symb) == stackSymbols.end() )
                            {
                                std::cerr << "Invalid push symbol: "<< symb
                                    <<"\nA push symbol must be present in StackAlphabet."
                                    << " Skipping to next symbol..."<<std:: endl;
                            }
                            else pushSymbols.push_back(symb);
                        }
                        else
                        {
                            std::cerr << "Invalid child element '" << runner2Tag
                                    << "' for transition." << std::endl;
                        }
                    }
                    Transition t(state, inputSymbol, stackSymbol, nextState, pushSymbols);
                    transitions.push_back(t);
                }
                else
                {
                    std::cerr << "Invalid child element '" << runnerTag
                            << "' for Transitions." << std::endl;
                }
            }
        }
        else
        {
            std::cerr << "Invalid child element '" << elemName
                    << "' for PDA." << std::endl;
        }
    }
    p = pda(states, alphabet, stackSymbols, transitions, startState, startSymbol, finalStates);
    return true;
}
