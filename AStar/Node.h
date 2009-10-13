/*
 * Node.h
 *
 *  Created on: 12 oct. 2009
 *      Author: clement
 */

#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include "GraphLib.h"

class Node {
	static Node * _refcounter[MAX_NODES];
	static int _nref;

	Node(int xx, int yy);

public:
	~Node();

	//Mem managment
	static Node * CreateNode(int x, int y);
	static void ReleaseAll();

	static float Distance(Node a, Node b);

	bool operator == (Node &a);

	int x;
	int y;
	float fcost;
	float hcost;
	float gcost;
	Node * parent;
};

#endif /* NODE_H_ */
