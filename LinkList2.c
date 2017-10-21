#include "LinkList2.h"

List *newList() {
	return NULL;
}


static List *makeNode(char *URL) {
	List *new = malloc(sizeof(List));
	new->URL = mystrdup(URL);
	new->next = NULL;	
	return new;
}


List *AddItem(List * head, char *URL) {
	List *new = makeNode(URL);
	if (head == NULL) {
		head = new;
	}
	else {
		List *temp;
		for (temp = head; temp->next != NULL; temp = temp->next) {
			;
		}
		temp->next = new;
	}
	return head;
}



void showList(List *head) {
	List *temp;
	for (temp = head; temp != NULL; temp = temp->next) {
		printf("%s %f -> ",temp->URL,temp->pagerank);
	}
	printf("\n");
}


List *assign_value(List *head, double pagerank, char *URL) {
	List *temp;
	
	for (temp = head; temp != NULL; temp = temp->next) {
		if(strcmp(temp->URL, URL) == 0){
			
			temp->pagerank = pagerank;
		}
	}
	return head;
}

int print_value_if_in_the_list(List *head, char *URL) {
	List *temp;
	int flag = 0;
	for (temp = head; temp != NULL; temp = temp->next) {
		if (strcmp(URL,temp->URL) == 0) {
			printf("%s\n", temp->URL);
			flag = 1;
			break;
		}
	}
	return flag;
}

