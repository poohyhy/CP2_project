#define MAX_PHONE_SIZE 100

typedef struct {
	char name[30];
	char phone[20];
	char memo[40];
} phone;

// 인자로 받은 문자열이 존재하는 PHONE구조체를 전부 출력
void tel_search(phone *, char *); 
// 인자로 받은 문자열 3개를 순서대로 name, phone, memo 순서로 phone구조체를 생성해 저장
void tel_add(phone *, char *, char *, char *);
// 인자로 받은 문자열이 존재하는 phone구조체를 출력하고 그중 선택하여 삭제
void tel_del(phone *, char *);
// name필드의 알파벳순으로 전체 리스트를 출력
void tel_print(phone *);