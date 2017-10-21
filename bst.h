#include "LinkList.h"
#include "c11.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bstNode
{
	struct bstNode *left;       /*Left Child*/
	struct bstNode *right;      /*Right Child*/
	char *key;
	StringList urlList;

}BSTNode;

BSTNode *BSTCreateTree();
void BSTDestroy(BSTNode *root);
BSTNode *BSTInsert(BSTNode *root, char *url, char *keyword);
BSTNode *BSTCreateNode(char *keyword, char* url);
void PrintInorder(BSTNode *root);
void Write_the_result(BSTNode *root, FILE **ptr);
void update_total_words(BSTNode *root, char *, int, int);
int get_length(BSTNode *root, char *key);
void getList(BSTNode *root, char * key, double *list, char**mystring);
