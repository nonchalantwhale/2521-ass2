#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include <math.h>

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;



// insert an Edge
// from v to w
void insertEdge(Graph g, Vertex v, Vertex w)
{
	if (v == w) {
		;
	}
	else if (g->edges[v][w] == 0) {
		g->edges[v][w] = 1;
		g->nE++;
	}
}


// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV * sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV * sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (w = 0; w < g->nV; w++) {
		for (v = 0; v < g->nV; v++) {
			printf("%d",g->edges[w][v]);
		}
		printf("\n");
	}
}

// counter represent the length of the array
// assume no self-loop
void PageRank_Calculation(Graph g, double d, double diffPR, int maxIterations, double *array, int *out_degree, int counter) {
	int i, a, b, c;
	double *prev = malloc(counter * sizeof(double));
	for (i = 0; i < counter; i++) {
		prev[i] = array[i];
	}
	int iteration = 0;
	double diff;
	diff = diffPR;
	while (iteration < maxIterations && diff >=diffPR) {
		iteration++;
		diff = 0;
		double nodein;
		double nodeout;
		double total_sum;
		// every node iteration
		for (i = 0; i < counter; i++) {
			nodein = nodeout = total_sum = 0;
			// calculate node in
			for (a = 0; a < counter; a++) {	
				// every nodes that connected to this node
				if (g->edges[a][i] == 1) {
					nodein++;				
				}
			}
			// calculate node out
			for (a = 0; a < counter; a++) {
				// every nodes that connected to this node
				if (g->edges[i][a] == 1) {
					nodeout++;
				}
			}		
			for (a = 0; a < counter; a++) {
				double sum1, sum2, W1, W2;
				sum1 = sum2 = W1 = W2 = 0;
				// every nodes that connected to this node
				if (g->edges[a][i] == 1) {					
					for (b = 0; b < counter; b++) {
						double cnt = 0;
						if (g->edges[a][b] == 1) {						
							for (c = 0; c < counter; c++) {
								if (g->edges[c][b]==1) {
									sum1++;
								}
								if (g->edges[b][c] == 1) {
									cnt++;
								}
							}
							if (cnt == 0) {
								sum2 += 0.5;
							}
							else {
								sum2 += cnt;
							}
						}					
					}
					W1 = nodein / sum1;					
					if (nodeout == 0) {
						W2 = 0.5 / sum2;
					}
					else {
						W2 = nodeout / sum2;
					}
					total_sum += prev[a] * W1 * W2;	
				}	
			}	
			array[i] = (1 - d) / counter + d * total_sum;
			diff += fabs(prev[i] - array[i]);	
			out_degree[i] = nodeout;
			
		}
		// updata the prev value
		for (i = 0; i < counter;i++) {
			prev[i] = array[i];
		}
	}
	free(prev);
}
