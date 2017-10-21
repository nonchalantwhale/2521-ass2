#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph.h"

#define URL_length 10
#define flag_length 20
#define path_length 100

int main(int argc, char *argv[]) {
	FILE *fp;
	int i;
	int counter = 0;
	char **myarray;
	char page[URL_length];
	fp = fopen("collection.txt", "r");
	if (fp == NULL) {
		printf("Can't open the file\n");
		return 1;
	}
	while (fscanf(fp,"%s",page) == 1) {
		counter++;
	}
	fclose(fp);
	
	myarray = malloc(counter * sizeof(char *));
	double *PageRank = malloc(counter * sizeof(double));
	int *out_degree = malloc(counter * sizeof(int));;
	counter = 0;
	fp = fopen("collection.txt", "r");
	while (fscanf(fp, "%s", page) == 1) {
		myarray[counter] = malloc(URL_length * sizeof(char)); 
		strcpy(myarray[counter], page);
		counter++;
	}
	fclose(fp);
	// initialse PageRank array
	for (i = 0; i < counter;i++) {
		PageRank[i] = 1 / (double)counter;
	}
	
	Graph myGraph = newGraph(counter);
	

	for (i = 0; i < counter;i++) {
		char temp[flag_length];
		char path[path_length] = {};
		strcat(path, myarray[i]);
		strcat(path, ".txt");
		
		fp = fopen(path, "r");
		if (fp == NULL) {
			printf("Can't open this txt\n");
		}
		// open successfully
		int flag;
		while (fscanf(fp,"%s",temp) != EOF) {
			
			int j;
			if (strcmp(temp, "#start") == 0) {
				// start
				flag = 0;
				continue;
			}
			if (strcmp(temp, "#end") == 0) {
				// stop because finished
				flag = 1;
				continue;
			}
			if (strcmp(temp, "Section-1") == 0) {
				if (flag == 0) {
					flag = 2;
				}
				else {
					flag = 1;
				}
				continue;
			}
			if (strcmp(temp, "Section-2") == 0) {
				if (flag == 0) {
					flag = 4;
				}
				else {
					flag = 1;
				}
				continue;
			}
			if (flag == 2) {
				for (j = 0; j < counter; j++) {
					if (strcmp(myarray[j], temp) == 0) {
						
						insertEdge(myGraph, i, j);
					}
				}
			}
			
		}
	
	}
	// showGraph(myGraph);
	// Test if the graph representation is correct
	// build graph successfullly
	if (argc != 4) {
		printf("number of arguments is not correct.\n");
	}
	int j;
	double sum_page = 0;
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);

	int maxIteration = atoi(argv[3]);
	PageRank_Calculation(myGraph, d, diffPR, maxIteration, PageRank, out_degree, counter);
	for (i = 0; i < counter;i++) {
		sum_page += PageRank[i];
	}
	

	FILE *ptr = fopen("pagerankList.txt", "w");

	// bubble sort
	for (i = 0; i < counter-1; i++) {
		for (j = 0; j < counter - i-1; j++)
			if (PageRank[j] < PageRank[j + 1]) {
				int temp1;
				double temp2;
				char temp3[flag_length];
				temp2 = PageRank[j];
				PageRank[j] = PageRank[j + 1];
				PageRank[j + 1] = temp2;

				temp1 = out_degree[j];
				out_degree[j] = out_degree[j + 1];
				out_degree[j + 1] = temp1;

				strcpy(temp3, myarray[j]);
				strcpy(myarray[j], myarray[j + 1]);
				strcpy(myarray[j + 1], temp3);
			}
	}

	for (i = 0; i < counter;i++) {
		fprintf(ptr, "%s, %d, %.7f\n", myarray[i], out_degree[i], PageRank[i]);
	}
	fclose(ptr);
	return 0;
}
