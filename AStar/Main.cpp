/*
 * Main.cpp
 *
 *  Created on: 12 oct. 2009
 *      Author: clement
 */

#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <time.h>

#include "Node.h"
#include "Graph.h"

void CallAll()
{
	Graph *g = new Graph(32,32);
	g->SetValue(2,0,10);
	g->SetValue(1,0,10);
	g->SetValue(2,1,10);
	g->SetValue(4,2,10);
	g->SetValue(10,10,10);
	g->SetValue(10,3,10);
	g->SetValue(10,3,10);
	Node start(0,0);
	Node end(31,10);
	g->SetValue(31,13,10);
	g->SetValue(30,14,10);
	g->SetValue(29,14,10);
	g->SetValue(28,15,10);
	g->SetValue(31,14,10);
	g->SetValue(31,16,10);
	for (int i=0;i<10000;i++)
	{
		g->FindPath(&start,&end);
	}
	delete g;
}

int main(int argc, char ** argv)
{
	CallAll();

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

	return 0;
}
