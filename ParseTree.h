/*
 * ParseTree.h
 *
 *  Created on: Dec 19, 2016
 *      Author: robbe
 */

#ifndef PARSETREE_PARSETREE_H_
#define PARSETREE_PARSETREE_H_

#include "Node.h"
#include <fstream>

class ParseTree {
public:
	ParseTree();
	ParseTree(shared_ptr<Node> root);

	void to_dot(string filename);

	virtual ~ParseTree();

private:
	std::shared_ptr<Node> root;
};

#endif /* PARSETREE_PARSETREE_H_ */
