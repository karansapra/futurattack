/*
 * NodeList.h
 *
 *  Created on: 12 oct. 2009
 *      Author: clement
 */

#ifndef NODELIST_H_
#define NODELIST_H_

#include <stdio.h>
#include "Node.h"
#include "GraphLib.h"

class NodeList {
	Node * _nodes[MAX_NODES_IN_LIST];
	int _nnodes;

public:
	NodeList();
	virtual ~NodeList();

	void Add(Node * node);

	int Size();

	void Delete(Node * node);

	/*
	 * Compare selon les coordonnées, pas selon le pointeur!
	 * renvoie le pointeur de la liste en echange
	 */
	Node* Exists(Node * node);

	/*
	 * Renvoie le meilleur noeud avec le meilleur F Score
	 */
	Node * FindByFScore();

	void Clear();

};

#endif /* NODELIST_H_ */
