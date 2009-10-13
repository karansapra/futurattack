/*
 * NodeList.cpp
 *
 *  Created on: 12 oct. 2009
 *      Author: clement
 */

#include "NodeList.h"

NodeList::NodeList() {
	_nnodes = 0;
	for (int i=0;i<MAX_NODES_IN_LIST;i++)
		_nodes[i]=NULL;
}

NodeList::~NodeList() {

}

Node * NodeList::Exists(Node *node)
{
	for (int i=0;i<_nnodes;i++)
		if (*_nodes[i]==*node)
			return _nodes[i];

	return NULL;
}


int NodeList::Size()
{
	return _nnodes;
}

Node * NodeList::FindByFScore()
{
	Node * best;
	if (_nnodes>0)
		best = _nodes[0];
	else
		return NULL;

	for (int i=0;i<_nnodes;i++)
		if (_nodes[i]->fcost < best->fcost)
			best = _nodes[i];

	return best;
}



void NodeList::Delete(Node *node)
{
	int i=0;
	while (_nodes[i]!=node)
		i++;

	for (int j=i;j<_nnodes-1;j++)
		_nodes[j]=_nodes[j+1];

	_nnodes--;
}



void NodeList::Add(Node *node)
{
	_nodes[_nnodes++] = node;
}

void NodeList::Clear()
{
	_nnodes=0;
}




