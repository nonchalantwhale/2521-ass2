#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "StrDict.h"
#include "SList.h"
#include "SList.c"
#include "StrDict.c"
typedef struct _elem {
    
    char *name;
    float *places;
    int nPrefs;
}elem;

static double scaledFoot(char *page, int pos, StrDict *ranks, int nRanks, int cSize) {

    double sum = 0;
    for (int i = 0; i < nRanks; i++) {
    
        int rank = lookup(ranks[i], page);  //T_i(c)
        if (rank == -1) continue;    //not in this rank list
        
        sum += fabs((double)rank/(double)nEntries(ranks[i]) - (double)pos/(double)cSize);
    }
    return sum;
}

static void printPrefs(elem *prefs, int nmemb) {

    for (int d = 0; d < nmemb; d++) {
        printf("%s, ", prefs[d].name);
        
        for (int p = 0; p < nmemb; p++) {
            printf("%.4f ", prefs[d].places[p]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s {rank list}\n", argv[0]);
        exit(1);
    }

    int nRanks = argc-1;

    StrDict *ranks = calloc(sizeof(StrDict), argc-1); //page-position dictionary (T_i corresponds to rank[i-1])
    
    for (int i = 0; i < nRanks; i++) {
        ranks[i] = newStrDict();
    }

    SList pages = newSList();
    int file = 1;
    while (file <= nRanks) {   //for each rank file

        FILE *rankf = fopen(argv[file], "r");
        char lineBuf[512] = {0};
        int line = 1;
        //printf("opening %s\n", argv[file]);
        while (lineBuf == fgets(lineBuf, 512, rankf)) {    //for each page in the rank
        
            lineBuf[strlen(lineBuf)-1] = '\0';      //strip newline
            pages = addStr(pages, lineBuf);
            ranks[file-1] = addIndex(ranks[file-1], line, lineBuf);
            line++;
        }
        fclose(rankf);
        file++;
    }
    
    int nPages = nStr(pages);
    elem *prefs = calloc(sizeof(elem), nPages);    //array of each page and their pos preferences
    if (prefs == NULL) abort();
    
    for (int a = 0; a < nPages; a++) {
        
        pages = popFirstStr(pages, &(prefs[a].name));    //add name to preference
        prefs[a].places = calloc(sizeof(int), nPages);
        if (prefs[a].places == NULL) abort();
    }
    //debugging
    //printf("%d, %d\n", nEntries(ranks[0]),nEntries(ranks[1]));
    
    //PREFERENCE: position where W(c, p) is minimal
    /*we now have our table:
    url#    url#    url#
    ...     ...     ...
    ...     ...     ...
    */
    //we will now iterate through each url from 0 to nPages-1, and add its preferences
    
   for (int i = 0; i < nPages; i++) {
        
        for (int p = 0; p < nPages; p++) {
            
            prefs[i].places[p] = scaledFoot(prefs[i].name, p+1, ranks, nRanks, nPages);
            prefs[i].nPrefs++;
        }
    }
    
    printPrefs(prefs, nPages);
    
    
    
    for (int i = 0; i < nRanks; i++)    //clean up
        freeStrDict(ranks[i]);
    
    for (int d = 0; d < nPages; d++) {
        free(prefs[d].name);
        free(prefs[d].places);
    }
    free(prefs);
    free(ranks);
        
    return EXIT_SUCCESS; 
}
/*
void position(c, p){
    double storage;
    int sum_cp[50] = 0;
    int  i, a

    while (i <= k) {
        storage = fabs((c/n)-(p/n));
        sum_cp[a] = sum_cp[a] + storage;
         

        c++;
        i++;
        a++;

    }
}
*/

void swap(char *str1, char *str2) {
    char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
    strcpy(temp, str1); // put str1 into temp 
    strcpy(str1, str2); // put str 2 in str1
    strcpy(str2, temp); // put temp (str1) into str2 
    free(temp); // free once swapped 
} 


void calculation (char **a, int l, int r) {

    int b, c, d, i, j; 
    int length;
    int max; 
    char ***T;
    if (l == r) {
        // base case
        // start calculation
        double box = 0;
        double mini = 999;

        int e = 0;
        while (e<= r) {
            e++; 
        }

        int t;  
        int b = 0;
        while (b < t) {
            int mylength, x = 0;
            while (x < max) {
                if (strcmp(T[b][c],"") == 0) {
                    ;  
                } else {
                    mylength++; 
                }
                c++;
            }
            int c = 0;
            while (c < max) {
                if (strcmp(T[b][c], "") == 0) {
                    ;
                } else {
                    int positon, d =0;
                    while(d < length) {
                        if (strcmp(T[b][c],a[d])==0) {
                            positon++;
                            break;
                        } else {
                            positon++;
                        }
                        d++;
                    }
                    box += fabs((double)(c+1)/mylength-(double)positon/length);
                    // The main calculation formula 
                }
                c++;
            }
            b++;
        }
       
        if (box < mini) {
            mini = box;
        }  
    } else {
        int i = l;
        while (i <= r) {
            swap(a[l], a[i]);
            calculation(a, l + 1, r);
            swap(a[l], a[i]); 
            i++;
        } 
    }
}



