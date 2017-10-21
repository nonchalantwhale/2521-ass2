#include "bst.h"



BSTNode* BSTCreateTree() {
	return NULL;
}

BSTNode* BSTCreateNode(char *keyword, char* url)
{
	BSTNode* node = malloc(sizeof(BSTNode));
	assert(node != NULL);
	node->left = NULL;
	node->right = NULL;
	node->key = mystrdup(keyword);
	node->urlList = newStringList(url);
	return node;
}


void BSTDestroy(BSTNode *root)
{
	if (root)
	{
		if (root->left)
			BSTDestroy(root->left);
		if (root->right)
			BSTDestroy(root->right);
		free(root);
	}
}


BSTNode *BSTInsert(BSTNode *root, char *url, char *keyword)
{
	if (root == NULL) {
		root = BSTCreateNode(keyword, url);
		if (root == NULL) {
			printf("No enough space");
		}
	}
	else if (strcmp(keyword, root->key) < 0) {
		// indicate keywaord < key
		root->left = BSTInsert(root->left, url, keyword);
	}
	else if (strcmp(keyword, root->key) > 0) {
		root->right = BSTInsert(root->right, url, keyword);
	}
	else {
		// the key already exist
		// if the url node don't exist create a new node
		// if it doesn't exist, create a new node and initialize the occurcence to 1
		root->urlList = Insert_To_Same_key(root->urlList, url);
	}
	return root;
}

void PrintInorder(BSTNode *root) {
	if (root == NULL)
		return;

	/* first recur on left child */
	PrintInorder(root->left);

	/* then print the data of node */
	printf("%s ", root->key);
	showUrlList(root->urlList);

	/* now recur on right child */
	PrintInorder(root->right);
}

void Write_the_result(BSTNode *root, FILE **ptr) {
	if (root == NULL)
		return;


	Write_the_result(root->left, ptr);


	fprintf(*ptr, "%s ", root->key);
	PrintUrlList(root->urlList, ptr);


	Write_the_result(root->right, ptr);
}



void update_total_words(BSTNode *root, char *url, int total, int counter) {
	if (root == NULL) {
		return;
	}
	update_total_words(root->left, url, total, counter);

	update_total_words_in_list(root->urlList, url, total, counter);

	update_total_words(root->right, url, total, counter);
}

int get_length(BSTNode *root, char *key) {
	if (root == NULL) {
		return 0;
	}
	if (strcmp(root->key, key) == 0) {
		return get_list(root->urlList);
	}
	else if (strcmp(key, root->key) > 0) {
		return get_length(root->right, key);
	}
	else {
		return get_length(root->left, key);
	}
	
}


void getList(BSTNode *root, char * key, double *list, char** mystring) {
	if (root == NULL) {
		return;
	}
	if (strcmp(root->key, key) == 0) {
		 get_data(root->urlList, list, mystring);
	}
	else if (strcmp(key, root->key) > 0) {
		getList(root->right, key,list,mystring);
	}
	else {
		getList(root->left, key,list,mystring);
	}
}
