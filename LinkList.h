#include <stdio.h>
#include "c11.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

typedef struct StringListRep *StringList;

// create a new StringList
StringList newStringList(char *url);

// free up all space associated with list
void freeStringList(StringList);
StringList Insert_To_Same_key(StringList L, char *url);
void showUrlList(StringList L);
void PrintUrlList(StringList L, FILE **ptr);
void update_total_words_in_list(StringList L, char *,int, int);
int get_list(StringList L);
void get_data(StringList L, double *,char **);
