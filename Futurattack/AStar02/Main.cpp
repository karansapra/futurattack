/*
 * Main.cpp
 *
 *  Created on: 12 oct. 2009
 *      Author: clement
 */

#include <stdio.h>
#include <stdlib.h>

#include "Node.h"
#include "Graph.h"

int main(int argc, char ** argv)
{
	Graph *g = new Graph(10,3);
	g->SetValue(2,0,10);
	g->SetValue(1,0,10);
	g->SetValue(2,1,10);
	Node *start = Node::CreateNode(0,0);
	Node *end = Node::CreateNode(8,0);
	g->FindPathAndSavePPM(start,end,"/home/clement/Bureau/path.ppm");
	/*
	if (path!=NULL)
	{
		printf("Chemin trouve!\n");
		for (int i=0;i<path->ncoords;i++)
			printf(" (%d,%d)\n",path->coords[i].x,path->coords[i].y);
	} else
	{
		printf("Pas de chemin!\n");
	}
	*/
	Node::ReleaseAll();
	return 0;
}
