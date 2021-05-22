#define MAX_PHONE_SIZE 100

typedef struct PHONE{
	char *name;
	char *phone;
	char *memo;
	struct PHONE *link;
} PHONE;

void tel_how();
int *tel_search(PHONE *, char *); 
PHONE *tel_add(PHONE *, char *, char *, char *);
PHONE *tel_del(PHONE *, char *);
void tel_print(PHONE *);