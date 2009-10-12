/*
 * Node.cpp
 *
 *  Created on: 12 oct. 2009
 *      Author: clement
 */

#include "Node.h"

Node * Node::_refcounter[MAX_NODES];
int Node::_nref=0;

Node::Node(int xx, int yy) {
	x=xx;
	y=yy;
	fcost=0.0;
	hcost=0.0;
	gcost=0.0;
	parent=NULL;
}

float Node::Distance(Node a, Node b)
{
	float vx = a.x - b.x;
	float vy = a.y - b.y;
	return vx*vx+vy*vy;
}

Node::~Node() {
}

Node *Node::CreateNode(int xx, int yy)
{
	Node * n = new Node(xx,yy);
	_refcounter[_nref++];
	return n;
}

bool Node::operator ==(Node & a)
{
	return (a.x == x && a.y == y);
}

void Node::ReleaseAll()
{
	for (int i=0;i<_nref;i++)
		if (_refcounter[i]!=NULL)
			delete _refcounter[i];
}


