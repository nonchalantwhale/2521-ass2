#include "LinkList.h"
// data structures representing IntList

typedef struct stringlistNode {
	char *url;
	int occurrence;
	int total;
	double tf;
	double idf;
	double tf_idf;
	struct stringlistNode *next;
}StringListNode;

struct StringListRep {
	StringListNode *first;
	StringListNode *last;
};


// create a new IntListNode with value v
// (this function is local to this ADT)
static StringListNode *newStringListNode(char* url)
{
	StringListNode *n = malloc(sizeof(StringListNode));
	assert(n != NULL);
	n->url = mystrdup(url);
	n->occurrence = 1;
	n->total = 0;
	n->idf = 0;
	n->tf = 0;
	n->tf_idf = 0;
	n->next = NULL;
	return n;
}

// create a string list with only one word
StringList newStringList(char *url)
{
	struct  StringListRep* L;
	L = malloc(sizeof(struct StringListRep));
	assert(L != NULL);
	L->first = newStringListNode(url);
	L->last = L->first;
	return L;
}

// free up all space associated with list
void freeStringList(StringList L)
{
	// TODO

}


StringList Insert_To_Same_key(StringList L, char *url) {
	StringListNode *temp;
	int already_exist = 0;
	for (temp = L->first; temp != NULL; temp = temp->next) {
		if (strcmp(temp->url, url) == 0) {
			already_exist = 1;
			temp->occurrence++;
			break;
		}
	}
	if (already_exist == 0) {
		// bigger than last one
		StringListNode *new = newStringListNode(url);
		assert(new != NULL);
		if (L->first == NULL) {
			L->first = L->last = new;
			return L;
		}
		if (strcmp(url, L->last->url) > 0) {
			L->last->next = new;
			L->last = new;
		}
		else if (strcmp(url, L->first->url) < 0) {
			StringListNode *temp = L->first;
			L->first = new;
			new->next = temp;
		}
		else {
			for (temp = L->first; temp != NULL; temp = temp->next) {
				if (strcmp(url, temp->url) > 0 && strcmp(url, temp->next->url) < 0) {
					StringListNode *temp2 = temp->next;
					temp->next = new;
					new->next = temp2;
				}
			}
		}
	}
	return L;
}


void showUrlList(StringList L) {
	StringListNode *temp;
	for (temp = L->first; temp != NULL; temp = temp->next) {
		printf("%s-- ", temp->url);
	}
	printf("\n");
}


void PrintUrlList(StringList L, FILE **ptr) {
	StringListNode *temp;
	for (temp = L->first; temp != NULL; temp = temp->next) {
		if (temp->next == NULL) {
			fprintf(*ptr, "%s\n", temp->url);
		}
		else {
			fprintf(*ptr, "%s ", temp->url);
		}
	}
}

void update_total_words_in_list(StringList L, char *url, int total, int counter) {
	StringListNode *temp;
	int length = 0;

	for (temp = L->first; temp != NULL; temp = temp->next) {
		if (strcmp(url, temp->url) == 0) {
			temp->total = total;
			temp->tf = ((double)temp->occurrence) / total;
		}
	}
	for (temp = L->first; temp != NULL; temp = temp->next) {
		length++;
	}
	for (temp = L->first; temp != NULL; temp = temp->next) {
		temp->idf = log10(((double)counter) / length);
		temp->tf_idf = (temp->idf) * (temp->tf);
	}
}


int get_list(StringList L) {
	StringListNode *temp;
	int length = 0;
	for (temp = L->first; temp != NULL; temp = temp->next) {
		length++;
	}
	// printf("length is %d\n",length);
	return length;
}

void get_data(StringList L, double *list, char **mystring) {
	StringListNode *temp;
	int cnt = 0;
	for (temp = L->first; temp != NULL; temp = temp->next) {
		list[cnt] = temp->tf_idf;
		strcpy(mystring[cnt], temp->url);
		// printf("%f %s---", list[cnt], mystring[cnt]);
		cnt++;
	}
}
