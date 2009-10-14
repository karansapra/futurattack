/*
 * Graph.cpp
 *
 *  Created on: 12 oct. 2009
 *      Author: clement
 */

#include "Graph.h"

Graph::Graph(int width, int height) {
	_width = width;
	_height = height;
	_vals = new int[width*height];
	for (int i=0;i<width*height;i++)
		_vals[i]=0;
}

void Graph::SetValue(int x, int y, int value)
{
	if (x>=0 && y>=0 && x<_width && y<_height)
		_vals[y*_width+x]=value;
}

int Graph::GetValue(int x, int y)
{
	if (x>=0 && y>=0 && x<_width && y<_height)
		return _vals[y*_width+x];

	return -1;
}

Graph::~Graph() {
	delete[] _vals;
}

Path *Graph::FindPath(Node *start, Node *end)
{
	start->gcost = 0.0;
	start->hcost = Node::Distance(*start,*end);
	start->fcost = start->hcost;

	_open_list.Add(start);

	while (_open_list.Size()!=0)
	{
		Node * x = _open_list.FindByFScore();
		if (*x==*end)
		{
			Path * path = new Path;
			path->ncoords = 0;
			Node * n = x;
			do
			{
				path->coords[path->ncoords].x = n->x;
				path->coords[path->ncoords].y = n->y;
				path->ncoords++;
				n = n->parent;
			} while (n!=NULL);

			_open_list.Clear();
			_closed_list.Clear();

			Node::ReleaseAll();

			return path;
		}

		_open_list.Delete(x);
		_closed_list.Add(x);

		/*
		 * Regard des cases adjacentes
		 */
		for (int nx=x->x-1;nx<=x->x+1;nx++)
		{
			for (int ny=x->y-1;ny<=x->y+1;ny++)
			{
				if (GetValue(nx,ny)!=0)
					continue;

				if ((nx==x->x && ny==x->y) || (nx!=x->x && ny!=x->y))
					continue;

				Node * son = Node::CreateNode(nx,ny);
				if (_closed_list.Exists(son)!=NULL)
					continue;

				Node * open_list_son = _open_list.Exists(son);
				if (open_list_son!=NULL)
					son = open_list_son;
				else
					_open_list.Add(son);

				son->parent = x;
				son->gcost = x->gcost + Node::Distance(*son,*x);
				son->hcost = Node::Distance(*son,*end);
				son->fcost = son->hcost + son->gcost;

			}
		}
	}

	_open_list.Clear();
	_closed_list.Clear();

	Node::ReleaseAll();

	return NULL;
}


void Graph::FindPathAndSavePPM(Node * start, Node * end, const char * ppm_file)
{
	start->gcost = 0.0;
	start->hcost = Node::Distance(*start,*end);
	start->fcost = start->hcost;

	_open_list.Add(start);

	while (_open_list.Size()!=0)
	{
		Node * x = _open_list.FindByFScore();
		if (*x==*end)
		{
			/*
			 * PPM Open
			 */

			FILE * f = fopen(ppm_file,"w");
			if (f==NULL)
				return;

			fprintf(f,"P3\n");
			fprintf(f,"%d %d\n255\n",_width*30,_height*30);

			Node * n = x;
			do
			{
				SetValue(n->x,n->y,-100);
				n = n->parent;
			} while (n!=NULL);

			SetValue(start->x,start->y,-200);
			SetValue(end->x,end->y,-200);

			int v;
			for (int yy=0;yy<_height*30;yy++)
			{
				for (int xx=0;xx<_width*30;xx++)
				{
					v = _vals[((yy/30)*_width)+(xx/30)];
					if (v==0)
						fprintf(f,"0 0 0 ");
					else if (v==-100)
						fprintf(f,"255 0 0 ");
					else if (v==-200)
						fprintf(f,"0 255 0 ");
					else
						fprintf(f,"255 255 255 ");
				}
			}
			fclose(f);

			for (int i = 0 ; i<_width*_height;i++)
			{
				if (_vals[i]<0)
					_vals[i]=0;
			}

			_open_list.Clear();
			_closed_list.Clear();

			Node::ReleaseAll();
			return;
		}

		_open_list.Delete(x);
		_closed_list.Add(x);

		/*
		 * Regard des cases adjacentes
		 */
		for (int nx=x->x-1;nx<=x->x+1;nx++)
		{
			for (int ny=x->y-1;ny<=x->y+1;ny++)
			{
				if (GetValue(nx,ny)!=0)
					continue;

				if ((nx==x->x && ny==x->y) || (nx!=x->x && ny!=x->y))
					continue;

				Node * son = Node::CreateNode(nx,ny);
				if (_closed_list.Exists(son)!=NULL)
					continue;

				Node * open_list_son = _open_list.Exists(son);
				if (open_list_son!=NULL)
					son = open_list_son;
				else
					_open_list.Add(son);

				son->parent = x;
				son->gcost = x->gcost + Node::Distance(*son,*x);
				son->hcost = Node::Distance(*son,*end);
				son->fcost = son->hcost + son->gcost;

			}
		}
	}

	_open_list.Clear();
	_closed_list.Clear();
	Node::ReleaseAll();
}
