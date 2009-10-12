/*
 * Graph.h
 *
 *  Created on: 12 oct. 2009
 *      Author: clement
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "NodeList.h"
#include "GraphLib.h"

struct Coords
{
	int x;
	int y;
};

struct Path
{
	Coords coords[MAX_CASES_FOR_PATH];
	int ncoords;
};



class Graph {
	int _width;
	int _height;

	int * _vals;

	NodeList _open_list;
	NodeList _closed_list;

public:
	Graph(int width, int height);
	virtual ~Graph();

	void SetValue(int x, int y, int value);
	int GetValue(int x, int y);

	Path * FindPath(Node * start, Node * end);
	void FindPathAndSavePPM(Node * start, Node * end, const char * ppm_file);
};

#endif /* GRAPH_H_ */
