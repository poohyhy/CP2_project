#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

void tel_how() 
{
	printf("tel to show tips\ntel -a to add\ntel -d to delete\ntel -l to print\n");
}

int tel_search(PHONE *list, char *input, int size) 
{
	int count = 0;

	for(int i = 0; i < size; i++) {
		if (strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL ) {
			printf("%d %s %s %s\n", ++count, list[i].name, list[i].phone, list[i].memo);
		}
	}
	return count;
}

void tel_add(PHONE *list, char *name, char *phone, char *memo, int size) 
{	
	printf("\n%s %s %s\n\nadd? [Y/N]: ", name, phone, memo);
	char ch = getchar();
	if (ch == 'Y') {
		strcpy(list[size].name, name);
		strcpy(list[size].phone, phone);
		strcpy(list[size].memo, memo);
		FILE *fp = fopen("data.txt", "w");
		for(int i = 0; i < size+1; i++) {
			char *put = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
			strcpy(put, list[i].name);
			strcat(put, ":");
			strcat(put, list[i].phone);
			strcat(put, ":");
			strcat(put, list[i].memo);
			if(i < size) {
				strcat(put, "\n");
			}
			fputs(put, fp);
		}
	fclose(fp);
	}
}

void tel_del(PHONE *list, char *input, int size) 
{
	int arr[size];
	int count = 0;
	for(int i = 0; i < size; i++) {
		if(strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL) {
			printf("%d %s %s %s\n", ++count, list[i].name, list[i].phone, list[i].memo);
			arr[count] = i;
		}
	}
	printf("\nwhich one? ");
	int ch;
	scanf("%d", &ch);
	for(int ans = arr[ch]; ans < size; ans++) {
		list[ans] = list[ans+1];
	}
	FILE *fp = fopen("data.txt", "w");
	for(int i = 0; i < size-1; i++) {
		char *put = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
		strcpy(put, list[i].name);
		strcat(put, ":");
		strcat(put, list[i].phone);
		strcat(put, ":");
		strcat(put, list[i].memo);
		if(i < size-2) {
			strcat(put, "\n");
		}
		
		fputs(put, fp);
	}
	fclose(fp);
}

void tel_print(PHONE *list, int size) 
{
	for(int i = 0; i < size; i++) {
		printf("%d %s %s %s", i+1, list[i].name, list[i].phone, list[i].memo);
		printf("\n");
	}
}


int main(int argc, char *argv[])
{
	FILE *fp = fopen("data.txt", "r");
	PHONE list[100];
	int count = 0;

	while(!feof(fp)) {
		char *line = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
		fgets(line, MAX_PHONE_SIZE, fp);
		strcpy(list[count].name, strtok(line, ":"));
		strcpy(list[count].phone, strtok(NULL, ":"));
		strcpy(list[count].memo, strtok(NULL, ":\n"));
		count++;
	}
	fclose(fp);

	if (argc == 1) {
		tel_how();
		return 0;
	}
	else if (argc > 1) {
		if (strcmp(argv[1], "-a") == 0) {
			tel_add(list, argv[2], argv[3], argv[4], count);
		}
		else if (strcmp(argv[1], "-d") == 0) {
			tel_del(list, argv[2], count);
		}	
		else if (strcmp(argv[1], "-l") == 0) {
			tel_print(list, count);
		}
		else if (argc == 2) {
			int c = tel_search(list, argv[1], count);
			if (c == 0) {
				printf("\nno match found.\n");
			}
			else {
				printf("\nmatch found.\n");
			}
		}
	}

	fclose(fp);

	return 0;
}