#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

// 사용법 출력
void tel_how() 
{
	printf("tel to show tips\ntel word to search\ntel -a to add\ntel -d to delete\ntel -l to print\n");
}

// search
int tel_search(PHONE *list, char *input, int size) 
{
	int count = 0;
	// 각 PHONE구조체의 필드에서 입력된 문자열이 있는지 검사하여 있으면 출력하고 count 증가
	for(int i = 0; i < size; i++) {
		if (strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL ) {
			printf("%d %s %s %s", ++count, list[i].name, list[i].phone, list[i].memo);
		}
	}
	return count;
}

// add
void tel_add(PHONE *list, char *name, char *phone, char *memo, int size) 
{	
	// 입력된 정보 확인, add 여부 확인
	printf("\n%s %s %s\n\nadd? [Y/N]: ", name, phone, memo);
	char ch = getchar();
	if (ch == 'Y') {
		// 배열의 끝 PHONE구조체에 입력된 정보 복사
		strcpy(list[size].name, name);
		strcpy(list[size].phone, phone);
		strcpy(list[size].memo, memo);
		// data.txt파일 쓰기 모드로 열기. 
		FILE *fp = fopen("data.txt", "w");
		// 각 구조체의 필드를 ":"를 구분자로 하여 한 줄로 합치고,
		// 이를 배열의 처음부터 다시 입력하고 파일에 덮어쓰기
		for(int i = 0; i < size+1; i++) {
			char *put = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
			strcpy(put, list[i].name);
			strcat(put, ":");
			strcat(put, list[i].phone);
			strcat(put, ":");
			strcat(put, list[i].memo);
			if(i == size) {
				strcat(put, "\n");
			}
			fputs(put, fp);
		}
		// 파일 닫기
		fclose(fp);
	}
}

// delete
void tel_del(PHONE *list, char *input, int size) 
{
	int arr[size]; // 검색된 구조체의 list내 인덱스를 저장할 배열
	int count = 0;
	// 입력받은 문자열이 있는 PHONE구조체 검색하고 출력
	for(int i = 0; i < size; i++) {
		if(strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL) {
			printf("%d %s %s %s", ++count, list[i].name, list[i].phone, list[i].memo);
			arr[count] = i;
		}
	}
	// 검색된 정보가 없을때
	if (count == 0) {
		printf("no match found\n");
	}
	else {
		// 검색되어 출력된 PHONE구조체 중 삭제할 구조체를 입력받음
		printf("\nwhich one? ");
		int ch;
		scanf("%d", &ch);
		// 선택된 구조체의 다음 인덱스부터 한칸씩 앞으로 복사하여 삭제
		for(int ans = arr[ch]; ans < size; ans++) {
			list[ans] = list[ans+1];
		}
		// data.txt에 변경된 리스트 덮어쓰기
		FILE *fp = fopen("data.txt", "w");
		for(int i = 0; i < size-1; i++) {
			char *put = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
			strcpy(put, list[i].name);
			strcat(put, ":");
			strcat(put, list[i].phone);
			strcat(put, ":");
			strcat(put, list[i].memo);
			fputs(put, fp);
		}
		fclose(fp);
	}
}

int cmpstr(void const *a, void const *b) {
    char const *aa = (char const *)a;
    char const *bb = (char const *)b;

    return strcmp(aa, bb);
}
// list
void tel_print(PHONE *list, int size) 
{
	PHONE tmp;
	// 요소가 0개면 오류메세지 출력, 1개 이하이면 그냥 출력
	if (size == 0) {
		printf("empty\n");
	}
	if (size == 1) {
		for(int i = 0; i < size; i++) {
			printf("%d %s %s %s", i+1, list[i].name, list[i].phone, list[i].memo);
		}
	}
	// 요소가 2개 이상이면 name필드를 strcmp로 qsort하여 알파벳순 정렬
	else if (size >= 2) {
		qsort(list, size, sizeof(PHONE), cmpstr);
		for(int i = 0; i < size; i++) {
			printf("%d %s %s %s", i+1, list[i].name, list[i].phone, list[i].memo);
		}	
	}
}


int main(int argc, char *argv[])
{
	PHONE *list = (PHONE *)malloc(sizeof(PHONE) * 100); // PHONE 구조체 배열 동적으로 선언
	int count = 0; // 저장된 요소의 개수

	// data.txt 파일 줄단위로 끝까지 읽어 ":"를 구분자로 하여 각 구조체의 필드 입력
	FILE *fp = fopen("data.txt", "r");
	while(!feof(fp)) {
		char *line = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
		fgets(line, MAX_PHONE_SIZE, fp);
		// 빈 줄이 있으면 건너뛰기
		if (strcmp(line, "\0") == 0) {
			continue;
		}
		strcpy(list[count].name, strtok(line, ":"));
		strcpy(list[count].phone, strtok(NULL, ":"));
		strcpy(list[count].memo, strtok(NULL, ":"));
		count++;
	}
	fclose(fp);

	// 기본 작동
	if (argc == 1) {
		tel_how();
		return 0;
	}
	// command line args로 옵션 입력 시
	else if (argc > 1) {
		// "-a" 입력 시
		if (strcmp(argv[1], "-a") == 0) {
			tel_add(list, argv[2], argv[3], argv[4], count);
		}
		// "-d" 입력 시
		else if (strcmp(argv[1], "-d") == 0) {
			tel_del(list, argv[2], count);
		}
		// "-l" 입력 시	
		else if (strcmp(argv[1], "-l") == 0) {
			tel_print(list, count);
		}
		// 검색할 문자열 입력 시
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
	return 0;
}
