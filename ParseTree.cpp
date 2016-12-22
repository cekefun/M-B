/*
 * ParseTree.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: robbe
 */

#include "ParseTree.h"

ParseTree::ParseTree():root(0) {

}

ParseTree::ParseTree(shared_ptr<Node> root):root(root){

}

ParseTree::~ParseTree() {
}

void ParseTree::to_dot(string filename) {

	ofstream write(filename);

	if(write.is_open()){

		write << "graph {"<< "\n";
		list<shared_ptr<Node>> queue;
		queue.push_back(this->root);
		int counter = 0;
		int child_count = 0;
		while(!queue.empty()){

			shared_ptr<Node> parent = queue.front();
			queue.pop_front();

			write <<"{"<< std::to_string(counter)<<"[label=\"" << parent->get_info()
			<< "\"]} -- { " ;

			list<shared_ptr<Node>> children = parent->get_children();
			for(auto el = children.begin(); el != children.end();el++){
				child_count++;
				write << child_count << " ";
				queue.push_back(*el);
			}

			write << "}" << "\n";
			counter++;
		}

		write << "}\n";
	}
}

