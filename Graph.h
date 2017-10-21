
// Graph.h ... interface to Graph ADT
// Written by John Shepherd, March 2013

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

// graph representation is hidden
typedef struct GraphRep *Graph;

// vertices denoted by integers 0..N-1
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct { Vertex v; Vertex w; } Edge;
void insertEdge(Graph, Vertex, Vertex);

// operations on graphs
Graph newGraph(int nV);
void dropGraph(Graph);
void showGraph(Graph);
void PageRank_Calculation(Graph g, double d, double diffPR, int maxIterations, double *array, int *out_degree,int counter);
#endif
