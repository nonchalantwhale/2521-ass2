#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define URL_length 10
#define flag_length 20
#define path_length 100

char *normalise(char *);

int main(int argc, char *argv[]) {
	FILE *fp;
	int i;
	BSTNode* newTree = BSTCreateTree();
	int counter = 0;
	char **myarray;
	char page[URL_length];
	fp = fopen("collection.txt", "r");
	if (fp == NULL) {
		printf("Can't open the file\n");
		return 1;
	}
	while (fscanf(fp, "%s", page) == 1) {
		// printf("page is %s\n", page);
		counter++;
	}
	fclose(fp);
	// printf("counter is %d\n",counter);
	myarray = malloc(counter * sizeof(char *));
	counter = 0;
	fp = fopen("collection.txt", "r");
	while (fscanf(fp, "%s", page) == 1) {
		myarray[counter] = malloc(URL_length * sizeof(char));
		strcpy(myarray[counter], page);
		counter++;
	}
	fclose(fp);
	int *total_words = malloc(sizeof(int) * counter);
	for (i = 0; i < counter; i++) {
		int j = 0;
		char temp[flag_length];
		char path[path_length] = {};
		strcat(path, myarray[i]);
		strcat(path, ".txt");
		//printf("path is %s \n",path);
		fp = fopen(path, "r");
		if (fp == NULL) {
			printf("Can't open this txt\n");
		}
		// open successfully
		int flag;
		while (fscanf(fp, "%s", temp) != EOF) {
			// printf("temp is %s\n",temp);
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
			if (flag == 4) {
				newTree = BSTInsert(newTree, myarray[i], normalise(temp));
				j++;
			}
		}
		// record how many words in one document
		total_words[i] = j;
	}
	for (i = 0; i < counter; i++) {
		// printf("total words is %d\n",total_words[i]);
		update_total_words(newTree, myarray[i], total_words[i], counter);
	}
	// PrintInorder(newTree);
	int a,b,c,d;
	
	for (a = 1; a < argc;a++) {
		int cnt = 0;
		// printf("%s\n",argv[a]);
		int length = get_length(newTree, argv[a]);
		// printf("length is %d\n",length);
		double *list = malloc(sizeof(double)*length);
		assert(list != NULL);
		char **mystring;
		mystring = malloc(length * sizeof(char *));
		for (b = 0; b < length;b++) {
			mystring[b] = malloc(sizeof(char) * URL_length);
		}
		getList(newTree, argv[a], list, mystring);
		
		
		// bubble sort
		for (c = 0; c <  length; c++) {
			for (d = 0; d < length - c - 1; d++)
				if (list[d] < list[d + 1]) {
					double temp2;
					char temp3[flag_length];
					

					temp2 = list[d];
					list[d] = list[d + 1];
					list[d+1] = temp2;

					strcpy(temp3, mystring[d]);
					strcpy(mystring[d], mystring[d + 1]);
					strcpy(mystring[d + 1], temp3);
				}
		}
		for (b = 0; b < length; b++) {
			printf("%s %.6f\n", mystring[b], list[b]);
			cnt++;
			if (cnt > 30) {
				break;
			}
		}
		printf("\n");
		
	}
	BSTDestroy(newTree);

}

char *normalise(char *ch) {
    int i;
    char *tempChar, *tempStr;
    
    for(i = 0;i< strlen(ch);i++) {
        ch[i] = tolower(ch[i]);
    }
    //remove special ch value
    
    tempStr = tempChar = ch;
    while(*tempStr) {
    //do
        *tempChar = *tempStr++;
        if(*tempChar != '.' && *tempChar != ',' && *tempChar != ';' && *tempChar != '?' && *tempChar != ' ') {
            tempChar++;
        }
    }
    *tempChar = '\0';
    return ch;
}
    





