#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// k
#define URL_length 10
#define flag_length 20
#define path_length 100
#define MAX_Line 1000



char ***T;
// global 3d array i repersent T1,T2...,j,k
double mini = 999;
// i
int T_number;
// j
int max_url;
int union_length;

void swap(char *str1, char *str2)
{
	char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
	free(temp);
}

void permute(char **a, int l, int r)
{
	int i, j;
	int b, c, d;
	if (l == r) {
		// base case
		// start calculation
		double total = 0;
		for (j = 0; j <= r; j++) {
			// printf("%s  ", a[j]);
		}
		//printf("\n");
		for (b = 0; b < T_number;b++) {
			int mylength = 0;
			for (c = 0; c < max_url;c++) {
				if (strcmp(T[b][c],"")==0) {
					;
				}
				else {
					mylength++;
				}
			}
			// printf("mylenght is %d\n", mylength);
			for (c = 0; c < max_url; c++) {
				if (strcmp(T[b][c], "") == 0) {
					;
				}
				else {
					int positon = 0;
					for (d = 0; d < union_length;d++) {
						if (strcmp(T[b][c],a[d])==0) {
							positon++;
							break;
							//printf("postion is %d\n",positon);
						}
						else {
							positon++;
						}
					}
					// printf("url is %s, postion oid is %d,now is %d\n",T[b][c],c,positon);
					total += fabs((double)(c+1)/mylength-(double)positon/union_length);
				}
			}
		}
		// printf("toatal is %f\n",total);
		if (total < mini) {
			mini = total;
		}

	}
	else
	{
		for (i = l; i <= r; i++)
		{
			swap(a[l], a[i]);
			permute(a, l + 1, r);
			swap(a[l], a[i]); //backtrack
		}
	}
}

void permute2(char **a, int l, int r)
{
	int i, j;
	int b, c, d;
	if (l == r) {
		// base case
		// start calculation
		double total = 0;
		
		for (b = 0; b < T_number; b++) {
			int mylength = 0;
			for (c = 0; c < max_url; c++) {
				if (strcmp(T[b][c], "") == 0) {
					;
				}
				else {
					mylength++;
				}
			}
			// printf("mylenght is %d\n", mylength);
			for (c = 0; c < max_url; c++) {
				if (strcmp(T[b][c], "") == 0) {
					;
				}
				else {
					int positon = 0;
					for (d = 0; d < union_length; d++) {
						if (strcmp(T[b][c], a[d]) == 0) {
							positon++;
							break;
							//printf("postion is %d\n",positon);
						}
						else {
							positon++;
						}
					}
					// printf("url is %s, postion oid is %d,now is %d\n",T[b][c],c,positon);
					total += fabs((double)(c + 1) / mylength - (double)positon / union_length);
				}
			}
		}

		/*
		for (j = 0; j <= r; j++) {
			printf("%s  ", a[j]);
		}
		printf("\n");
		printf("toatal is %f\n",total);
		*/
	
		if (fabs(total-mini)<0.01) {
		    printf("%f\n",total);
			// printf("result\n");
			for (j = 0; j <= r; j++) {
				printf("%s\n", a[j]);
			}
			printf("\n");
		}


	}
	else
	{
		for (i = l; i <= r; i++)
		{
			swap(a[l], a[i]);
			permute2(a, l + 1, r);
			swap(a[l], a[i]); //backtrack
		}
	}
}




int main(int argc, char *argv[]) {
	int i, j, k;
	char str1[URL_length];
	int max_length = -999;
	for (i = 1; i < argc;i++) {
		int cnt = 0;
		char base[path_length] = "";
		strcat(base, argv[i]);
		// printf("%s\n",base);
		FILE *ptr = fopen(base,"r");
		if (ptr == NULL) {
			printf("Failed on open file\n");
			return 1;
		}
		while(fscanf(ptr,"%s",str1)==1){
			//printf("%s   ", str1);
			cnt++;
		}
		//printf("\n");
		fclose(ptr);

		char **myarray = malloc(cnt * sizeof(char *));
		
		cnt = 0;
		FILE *ptr2 = fopen(base, "r");
		while (fscanf(ptr2, "%s", str1) == 1) {
			myarray[cnt] = malloc(URL_length * sizeof(char));
			strcpy(myarray[cnt], str1);
			cnt++;
		}
		fclose(ptr2);
		if (cnt>max_length) {
			max_length = cnt;
		}
		for (j = 0; j < cnt; j++) {
			// printf("%s\n", myarray[j]);
		}
		
		
	}
	// printf("max is %d\n",max_length);
	// printf("agrc is %d\n",argc);
	max_url = max_length;
	T_number = argc-1;
	T = malloc((argc-1) * sizeof(char **));

	for (i = 0; i < argc-1; i++) {
		T[i] = malloc(max_length * sizeof(char*));
		for (j = 0; j < max_length; j++) {
			T[i][j] = malloc(URL_length * sizeof(char));
			for (k = 0; k < URL_length;k++) {
				T[i][j][k] = 0;
			}
		}
	}
	// defuck no idea what going on, but the bug gone for no reason
	for (i = 1; i < argc; i++) {
		int cnt = 0;
		char base2[path_length] = "";
		strcat(base2, argv[i]);
		// printf("%s\n",base);
		FILE *ptr = fopen(base2, "r");
		if (ptr == NULL) {
			printf("Failed on open file\n");
			return 1;
		}
		while (fscanf(ptr, "%s", str1) == 1) {
			//printf("%s   ", str1);
			cnt++;
		}
		fclose(ptr);

		char **myarray = malloc(cnt * sizeof(char *));

		cnt = 0;
		FILE *ptr2 = fopen(base2, "r");
		while (fscanf(ptr2, "%s", str1) == 1) {
			myarray[cnt] = malloc(URL_length * sizeof(char));
			strcpy(T[i-1][cnt], str1);
			cnt++;
		}
		fclose(ptr2);
	}
	// test 3d
	/*
	for (i = 0; i < 2;i++) {
		for (j = 0; j < max_length;j++) {
			printf("%s ",T[i][j]);
		}
		printf("\n");
	}
	*/
	int word_cnt = 0;
	char **myunion = malloc(30*sizeof(char *));
	for (i = 0; i < 30;i++) {
		myunion[i] = malloc(sizeof(char)*URL_length);
		for (j = 0; j < URL_length;j++) {
			myunion[i][j] = 0;
		}
	}

	for (j = 0; j < max_length; j++) {
		if (strcmp(T[0][j],"")==0) {
			;
		}
		else {
			strcpy(myunion[word_cnt], T[0][j]);
			word_cnt++;
		}
	}
	for (i = 1; i < 2; i++) {
		for (j = 0; j < max_length; j++) {
			// T[i][j] is a url
			int found = 0;
			for (k = 0; k < word_cnt;k++) {
				if (strcmp(T[i][j],"") == 0) {
					// empty string assume found
					found = 1;
				}
				if (strcmp(T[i][j], myunion[k]) == 0) {
					found = 1;
				}
			}
			if (found == 0) {
				strcpy(myunion[word_cnt],T[i][j]);
				printf("not found is %s,i %d, j %d\n", T[i][j],i,j);
				word_cnt++;
			}
		}
	}
	// test union
	// printf("word_cnt is %d\n",word_cnt);
	/*
	for (i = 0; i < word_cnt;i++) {
		printf("myuni is %s\n",myunion[i]);
	}
	*/
	union_length = word_cnt;
	// printf("start permutation\n");
	permute(myunion, 0, --word_cnt);
	// printf("%f\n",mini);
	permute2(myunion, 0, word_cnt);
	return 0;
}
