/*
 * CYK.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: robbe
 */

#include "CYK.h"
#include <math.h>

CYK::CYK(){

}

CYK::~CYK() {
}

bool CYK::operator()(string str, Grammar& g){

	vector<string> split;

	for(size_t i = 0 ; i < str.size() ; i++){
		string temp = "";
		temp += str[i];
		split.push_back(temp);
	}

    return this->run(split,g);


}

bool CYK::run(vector<string> str, Grammar& g){

	tree_table.clear();

	table.clear();
	table.push_back(basis(str,g));

	unsigned int length = str.size();
	for(unsigned int counter = 2;counter <= length; counter++){
		// bottom to top but we have row one == basis


		vector< vector< std::shared_ptr<Node>>> empty;
		this->tree_table.push_back(empty);
		unsigned int i = 1;
		unsigned int j = counter;
		vector<vector<string>> tt;
		while(j <= length){
			vector<string> set = calc_X(g,i,j);
			tt.push_back(set);
			i++;
			j++;
		}
		table.push_back(tt);
	}
	vector<vector<string>> t = table[table.size() -1];
	vector<string> set = t[t.size() - 1];
	for(size_t fin = 0 ; fin < set.size(); fin++){
		if(set[fin] == g.GetStart()){
			return true;
		}
	}

	return false;
}

void CYK::print_table(){

    cout << string_table();

}

string CYK::string_table(){

    stringstream ss;

    int big = 0;

    for(size_t i = 0; i < table.size(); i++){

        for(size_t k = 0 ; k < table[i].size();k++){
            int med = 0;
            for(size_t l = 0; l <table[i][k].size();l++){

                 med += table[i][k][l].size(); // biggest symbol

            }
            med += table[i][k].size() * 2 -2;
            if (big < med){

                big = med;
            }

        }


    }
    for (int i = table.size() - 1; i >= 0; i--){
        for (size_t k = 0 ; k < table[i].size();k++){
            ss << "|{";
            string tmpstring = "";

            for (size_t l = 0; l <table[i][k].size();l++){

                tmpstring += table[i][k][l];


                if(l != table[i][k].size() - 1 ){
                tmpstring +=  ", ";
                }

            }
            int rest = round((big - tmpstring.size())/2);
            ss << string(rest,' ') << tmpstring << string(rest,' ');
            ss << "}|";
        }

        ss << "\n";
    }

    return ss.str();
}

vector<ParseTree> CYK::get_parseTrees(Grammar& gram){

	vector<std::shared_ptr<Node>> top_vec = tree_table[tree_table.size()-1][0];

	vector<ParseTree> result;

	for(size_t i = 0; i < top_vec.size(); i++){

		if(top_vec[i]->get_info() == gram.GetStart() ){
			ParseTree tree(top_vec[i]);
			result.push_back(tree);
		}
	}
	return result;
}

vector<vector<string>> CYK::basis(vector<string> & str, Grammar& g ){

	map<string,vector<string>> reverse = reverse_dic(g);
	vector<vector<string>> result;
	vector<vector <std::shared_ptr<Node> >> basis;
	for(size_t i = 0 ; i < str.size(); i++){


		string s = str[i];



		vector<string> head = reverse[s]; // possible parents of our leafs.
		vector<std::shared_ptr<Node>> parent_vec;
		for(size_t i = 0; i < head.size(); i++ ){

			std::shared_ptr<Node> child(new Node(s));
			// the leaf node of our parse
			// tree. This are the terminals

			std::shared_ptr<Node> parent(new Node(head[i]));
			parent->add_child(child);
			child->set_parent(parent);
			parent_vec.push_back(parent);
		}

		basis.push_back(parent_vec);
		result.push_back(reverse[s]);
	}
	tree_table.push_back(basis);

	return result;
}

map<string,vector<string>> CYK::reverse_dic(Grammar& grammar) const{

	std::map<symbol,std::vector<word>> rules = grammar.GetRules(); //original rules
	vector<symbol> vars = grammar.GetVariables();

	map<string,vector<string>> result; // resulting map

	for(size_t i = 0 ; i < vars.size(); i++){ // all the variables are keys

		vector<word> body = rules[vars[i]];

		for(size_t j = 0; j < body.size(); j++){

			vector<symbol>  pr = body[j];

			for(size_t k = 0; k < pr.size(); k++){

				if(result.count(pr[k]) == 0){ // the symbol not yet in dic
					vector<string> t;
					t.push_back(vars[i]);
					result[pr[k]] = t;
				}

				else{
					vector<string>& symbol = result[pr[k]];
					symbol.push_back(vars[i]);
				}
			}
		}
	}

	return result;
}

vector<string> CYK::calc_X(Grammar& g, int i, int j){
	vector<string> result;
	int height = 0;
	if(j > i){
		height = j - i;
	}
	else{
		height = i - j;
	}

	vector<vector<string> >unions; // we need to know wich pairs we take union from

	vector<int> pair1_i; // finding back our pairs in the table.
	vector<int> pair1_j; // needed to merge subtrees into a bigger tree.
	vector<int> pair1_k;

	vector<int> pair2_i;
	vector<int> pair2_j;
	vector<int> pair2_k;

	for(int loop = 0 ; loop <height; loop++){

		vector<string> pair1 = table[loop][i -1] ; // in A => BC this is pos B
		vector<string> pair2 = table[(height -loop) - 1][i + loop] ; // This is C

		for(size_t p1 = 0; p1 < pair1.size(); p1++){
			for(size_t p2 = 0; p2 < pair2.size(); p2++){
				vector<string> temp;
				temp.push_back(pair1[p1]);
				temp.push_back(pair2[p2]);

				pair1_i.push_back(loop);
				pair1_j.push_back(i - 1);
				pair1_k.push_back(p1);

				pair2_i.push_back(height - loop -1);
				pair2_j.push_back(i + loop);
				pair2_k.push_back(p2);

				unions.push_back(temp);

			}
		}
	}

	map<string, vector<word>> mp = g.GetRules();
	map<string, vector<word>>::iterator it;

	vector<std::shared_ptr<Node>> extend_tree;

	for(it = mp.begin(); it != mp.end(); it++){
		vector<vector<string>> word = it->second;
		for(size_t k = 0 ; k < word.size(); k++){
			for(size_t l = 0 ; l < unions.size();l++){
				if(word[k] == unions[l]){
					bool checker = true;
					for(size_t test = 0 ; test < result.size(); test++){
						if(result[test] == it->first){
							checker = false;
							break;
						}
					}
					if(checker == true){
						result.push_back(it->first);

						std::shared_ptr<Node> node(new Node(it->first));

						unsigned int p_i = pair1_i[l];
						unsigned int p_j = pair1_j[l];
						unsigned int p_k = pair1_k[l];

						if(this->tree_table.size() > p_i){
							if(this->tree_table[p_i].size() > p_j){
								if(this->tree_table[p_i][p_j].size() > p_k){
									std::shared_ptr<Node> child1;
									child1 = this->tree_table[p_i][p_j][p_k];
									node->add_child(child1);
									child1->set_parent(node);
								}
							}
						}


						p_i = pair2_i[l];
						p_j = pair2_j[l];
						p_k = pair2_k[l];

						if(this->tree_table.size() > p_i){
							if(this->tree_table[p_i].size() > p_j){
								if(this->tree_table[p_i][p_j].size() > p_k){


									std::shared_ptr<Node> child1;
									child1 = this->tree_table[p_i][p_j][p_k];

									node->add_child(child1);
									child1->set_parent(node);
								}
							}
						}


						extend_tree.push_back(node);

					}
					break;
				}
			}
		}

	}
	this->tree_table[height].push_back(extend_tree);
	return result;
}

void CYK::print_nodes(){

	for(size_t i = 0; i < this->tree_table.size();i++){

		for(size_t j = 0; j < this->tree_table[i].size();j++){
			cout << "{";
			for(size_t k = 0; k < this->tree_table[i][j].size();k++){
				cout << tree_table[i][j][k]->get_info() << " ";
			}
			cout << "} ";
		}
		cout << endl;
	}

}

