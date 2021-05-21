#include <stdio.h>
#include "tel.h"

int main(int argc, char *argv[])
{
	if (argc == 1) {
		tel_how();
		return 0;
	}
	if else (argc > 1) {
		switch (argv[1]) {
			case "-a" : 
				tel_add();
				break;
			case "-d" : 
				tel_del();
				break;
			case "-l" : 
				tel_print();
				break;
			default :
				tel_search();
		}
	}
	return 0;
}