/*
 * Node.h
 *
 *  Created on: Dec 19, 2016
 *      Author: robbe
 */

#ifndef PARSETREE_NODE_H_
#define PARSETREE_NODE_H_

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

using namespace std;

class Node {
public:
	Node(string info);
	Node(string info, std::shared_ptr<Node> parent);

	virtual ~Node();

	void add_child(std::shared_ptr<Node>);
	void set_parent(std::shared_ptr<Node>);
	string get_info();

	list<std::shared_ptr<Node>> get_children();

	void to_lisp(std::ostream&);

private:

	string info;
	list <std::shared_ptr<Node>> children;
	std::shared_ptr<Node> parent;


};

#endif /* PARSETREE_NODE_H_ */
