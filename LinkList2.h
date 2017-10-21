#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "c11.h"

typedef struct list
{
	char *URL;
	double pagerank;
	struct list * next;
}List;

List *newList();
List *AddItem(List * head, char *URL);
void showList(List *head);
List *assign_value(List *head, double pagerank, char *URL);
int print_value_if_in_the_list(List *head, char *URL);
