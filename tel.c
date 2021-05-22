#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

void tel_how() 
{
	printf("tel to show tips\ntel -a to add\ntel -d to delete\ntel -l to print\n");
}

int *tel_search(PHONE *p, char *input) 
{
	int count[MAX_PHONE_SIZE];
	int i = 1;
	int j = 0;

	while(p != NULL) {
		if (strstr(p->name, input) != NULL || strstr(p->phone, input) != NULL || strstr(p->memo, input) != NULL) {
			printf("%s %s %s", p->name, p->phone, p->memo);
			count[j] = i;
			j++;
		}
		i++;
	}
	return count;
}

PHONE *tel_add(PHONE *list, char *name, char *phone, char *memo) 
{
	PHONE *p = (PHONE *)malloc(sizeof(PHONE));
	p->name = name;
	p->phone = phone;
	p->memo = memo;
	list = p;
	return list;
}

PHONE *tel_del(PHONE *list, char *input) 
{
	int *count = tel_search(list, input);
	
}

void tel_print(PHONE *list) 
{
	for(PHONE *p = list; p != NULL; p = p->link) {
		printf("%s %s %s\n", p->name, p->phone, p->memo);
	}
}


int main(int argc, char *argv[])
{
	FILE *fp = fopen("data.txt", "r+");
	
	while(!feof(fp)) {
		char line[MAX_PHONE_SIZE];
		fgets(line, MAX_PHONE_SIZE, fp);

	}

	if (argc == 1) {
		tel_how();
		return 0;
	}
	else if (argc > 1) {
		if (strcmp(argv[1], "-a") == 0) {
			printf("%s %s %s\n\nadd? [Y/N]: ", argv[2], argv[3], argv[4]);
			char ch = getchar();
			if (ch == 'Y') 
				tel_add(list, argv[2], argv[3], argv[4]);
		}
		if (strcmp(argv[1], "-d") == 0) {
			tel_del(list, argv[2]);
		}	
		if (strcmp(argv[1], "-l") == 0) {
			tel_print(list);
		}
		else {
			tel_search(list, argv[2]);
		}
	}
	return 0;
}