#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "func.h"
#include "StructureFunc.h"


int main()
{
	List test;
	createList(&test);
	fileRead(&test, "Status.txt");
	
	return 0;
}

void mainMenu()
{
	List list[5];
	int i;

	for (i = 0; i < sizeof(list) / sizeof(list[0]); i++) {
		createList(&list[i]);
		fileRead(&list[i], fileName[i]);
	}	// list[0] : dlist, list[1] : rlist,  list[2] : slist, list[3] : elist, list[4] : infolist

	while (1) {
		if (kbhit()) {
			//printMain(&list[2]);
		}

	}
}

