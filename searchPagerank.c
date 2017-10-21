#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "LinkList2.h"

#define URL_length 10
#define flag_length 20
#define path_length 100
#define MAX_Line 1000

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("The number of arguments aren't right\n");
		return 1;
	}
	int i;
	
	for (i = 1; i < argc; i++) {
		FILE *fp1 = fopen("invertedIndex.txt", "r");
		assert(fp1 != NULL);
		
		// curr contain the word to be searched
		char *curr = mystrdup(argv[i]);
		char temp[path_length] = "";
		char *key;
		const char s[2] = " ";
		// should use a read line function
		while (fgets(temp, MAX_Line, fp1) != NULL)
		{
			char *newline = strchr(temp, '\n');
			if (newline) {
				*newline = 0;
			}
			 key = strtok(temp, s);
			 if (strcmp(key, curr) == 0) {
				 int counter = 0;
				 List *mylist = newList();
				 while (key != NULL) {
					// skip the first time
					if (counter == 0) {
						key = strtok(NULL, s);
					}
					else {
						mylist = AddItem(mylist, key);
						key = strtok(NULL, s);
					}
					counter++;
				 }
				 //showList(mylist);
				 
				 FILE *fp2 = fopen("pagerankList.txt", "r");
				 assert(fp2 != NULL);
				 char temp1[flag_length];
				 char temp2[flag_length];
				 double temp3;
				 while (fscanf(fp2,"%s %s %lf",temp1,temp2,&temp3) == 3) {
					int length = strlen(temp1);
					temp1[length - 1] = '\0';
					mylist = assign_value(mylist, temp3, temp1);
				 }
				fclose(fp2);

				int cnt2 = 0;
				FILE *fp3 = fopen("pagerankList.txt", "r");
				assert(fp3 != NULL);
				while (fscanf(fp2, "%s %s %lf", temp1, temp2, &temp3) == 3) {
					int length = strlen(temp1);
					temp1[length - 1] = '\0';
					cnt2 += print_value_if_in_the_list(mylist, temp1);
					if (cnt2 >= 30) {
						break;
					}
				}
				printf("\n");
				fclose(fp3);
			 }
		}
		fclose(fp1);
	}
	return 0;
}
