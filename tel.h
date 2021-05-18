#define MAX_PHONE_SIZE 100

typedef struct {
	char name[30];
	char phone[20];
	char memo[40];
} phone;

void tel_how();
void tel_search(phone *, char *); 
void tel_add(phone *, char *, char *, char *);
void tel_del(phone *, char *);
void tel_print(phone *);