/*
 * Node.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: robbe
 */

#include "Node.h"

Node::Node(string info):info(info),parent(0) {

}

Node::Node(string info,Node* parent):info(info),parent(parent){

}

Node::~Node() {
}
void Node::add_child(std::shared_ptr<Node> child){

	this->children.push_back(child);
}

void Node::set_parent(std::shared_ptr<Node> parent){

	this->parent = parent;
}

string Node::get_info(){
	return this->info;
}

list<shared_ptr<Node>> Node::get_children(){

	return this->children;
}
