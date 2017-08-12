#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <windows.h>
#include "Structure.h"
#include "StructFunc.h"
#include "MainFunc.h"
#define AIRCOND 0
#define AIRCLEANER 1
#define COOK 2
#define INDUCTION 3
#define LAUND 4
#define TEMPER 5
#define ESC 27

const char *fileName[] = { "Device.txt", "Reserve.txt", "Status.txt", "Environ.txt", "Info.txt" };
char *deviceName[] = { "AIRCOND", "AIRCLEANER", "COOK", "INDUCTION", "LAUNDRY", "TEMPER" };

void mainMenu()
{
	List list[5];
	int i, choice;
	
	for (i = 0; i < sizeof(list) / sizeof(list[0]); i++) {
		createList(&list[i]);
		fileRead(&list[i], fileName[i]);
	}	// list[0] : dlist, list[1] : rlist,  list[2] : slist, list[3] : elist, list[4] : infolist

	while (1) {
		if (kbhit()) {
			choice = getch();
			if (choice >= 97 && choice <= 122)
				choice -= 32;
			else if (choice == ESC)
				break;
			
			switch (choice) {
			case 'O': power(&list[2]);
			}
		}
		printMain(&list[2]);
	}

	for (i = 0; i < sizeof(list) / sizeof(list[0]); i++)
		destroyList(&list[i]);
}

void fileRead(List *list,const char *fileName)
{
	if (!strcmp("Device.txt", fileName) || !strcmp("Info.txt", fileName))
		deviceRead(list, fileName);
	else if (!strcmp("Reserve.txt", fileName))
		reserveRead(list, fileName);
	else if (!strcmp("Status.txt", fileName))
		statusRead(list, fileName);
	else if (!strcmp("Environ.txt", fileName))
		environRead(list, fileName);
	else {
		printf("Cannot find the File !\n");
		return;
	}
}

void deviceRead(List *dlist, const char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	char nl;
	Device tmp;
	
	sprintf(realFile, "%s%s", "C:/Data/", fileName);

	fp = fopen(realFile, "rt");
	assert(fp != NULL);

	if (!strcmp("Device.txt", fileName)) {
		while (fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
			tmp.deviceName[strlen(tmp.deviceName) - 1] = '\0';
			fgets(tmp.company, sizeof(tmp.company), fp);
			tmp.company[strlen(tmp.company) - 1] = '\0';
			fgets(tmp.indate, sizeof(tmp.indate), fp);
			tmp.indate[strlen(tmp.indate) - 1] = '\0';
			fscanf(fp, "%d ", &tmp.reserCnt);
			addLast(dlist, &tmp, sizeof(Device), deviceMemcpy);
		}
	}
	else {
		deviceInit(&tmp);
		while (fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
			tmp.deviceName[strlen(tmp.deviceName) - 1] = '\0';
			fgets(tmp.company, sizeof(tmp.company), fp);
			tmp.company[strlen(tmp.company) - 1] = '\0';
			addLast(dlist, &tmp, sizeof(Device), deviceMemcpy);
		}
	}
}

void reserveRead(List *rlist, const char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	char nl;
	Reserve tmp;

	sprintf(realFile, "%s%s", "C:/Data/", fileName);

	fp = fopen(realFile, "rt");
	if (fp == NULL) return;

	while (fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
		tmp.deviceName[strlen(tmp.deviceName) - 1] = '\0';
		fscanf(fp, "%d", &tmp.hour);
		fscanf(fp, "%d", &tmp.min);
		fscanf(fp, "%d", &tmp.reStatus);
		fscanf(fp, "%d ", &tmp.mode);
		addLast(rlist, &tmp, sizeof(Reserve), reserveMemcpy);
	}
}

void statusRead(List *slist, const char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	char nl;
	Status tmp;

	sprintf(realFile, "%s%s", "C:/Data/", fileName);

	fp = fopen(realFile, "rt");
	if (fp == NULL) return;

	while (fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
		tmp.deviceName[strlen(tmp.deviceName) - 1] = '\0';
		fscanf(fp, "%d", &tmp.status);
		fscanf(fp, "%d", &tmp.mode);
		fscanf(fp, "%d ", &tmp.temper);
		addLast(slist, &tmp, sizeof(Status), statusMemcpy);
	}
}

void environRead(List *elist, const char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	char nl;
	Environ tmp;

	sprintf(realFile, "%s%s", "C:/Data/", fileName);

	fp = fopen(realFile, "rt");
	if (fp == NULL) return;

	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp.nowTemper);
		fscanf(fp, "%d", &tmp.clean);
		addLast(elist, &tmp, sizeof(Environ), environMemcpy);
	}
}

void power(List *slist)
{
	char choice;

	while (1) {
		if (kbhit()) {
			choice = getch();
			if (choice >= 97 && choice <= 122)
				choice -= 32;
			else if (choice == ESC)
				break;

			switch (choice) {
			case 'A':
				powerCheck(slist, AIRCOND);
				break;
			case 'B':
				powerCheck(slist, AIRCLEANER);
				break;
			case 'C':
				powerCheck(slist, COOK);
				break;
			case 'D':
				powerCheck(slist, INDUCTION);
				break;
			case 'E':
				powerCheck(slist, LAUND);
				break;
			case 'F':
				powerCheck(slist, TEMPER);
				break;
			}
		}
		printMain(slist);
	}
}

void powerCheck(List *slist, int index)
{
	Node *cur;
	Status *s;

	if ((cur = searchNode(slist, deviceName[index], statusNameCmp)) == NULL) {
		printf("등록되지 않은 장치입니다 !\n");
		return;
	}
	
	s = ((Status *)(cur + 1));

	if (s->status) {
		printf("\n\n\t\t\t\t\t%11s 을(를) OFF 합니다\n", s->deviceName);
		s->status = 0;
	}
	else {
		printf("\n\n\t\t\t\t\t%11s 을(를) ON 합니다\n", s->deviceName);
		s->status = 1;
	}
}

void printMain(List *slist)
{
	Node *cur;
	Status tmp;
	Status tmp2;
	char st[10] = { " " };
	char st2[10] = { " " };
	statusInit(&tmp);
	statusInit(&tmp2);
	int i = 0;
	int j = 0;
	gotoxy(3, 5);
	printf("+--------------------------------------------------------------------------------------------------------+");
	for (i = 0; i<6; i++)
	{

		strcpy(tmp.deviceName, deviceName[i]);
		strcpy(tmp2.deviceName, deviceName[i + 1]);
		cur = slist->head->next;
		while (cur != slist->tail) {
			if (statusNameCmp(cur + 1, &tmp))
			{
				statusMemcpy(&tmp, cur + 1);
				if (tmp.status == 1)
				{
					strcpy(st, "    ●");
				}
				else
				{
					strcpy(st, "    ○");
				}
			}
			cur = cur->next;
		}
		if (!strcmp(st, ""))
			strcpy(st, "미등록");

		cur = slist->head->next;
		while (cur != slist->tail)
		{
			if (statusNameCmp(cur + 1, &tmp2))
			{
				statusMemcpy(&tmp2, cur + 1);
				if (tmp2.status == 1)
					strcpy(st2, "    ●");
				else
					strcpy(st2, "    ○");
			}
			cur = cur->next;
		}
		if (!strcmp(st2, ""))
			strcpy(st2, "미등록");

		gotoxy(3, 6 + (5 * j));
		printf("| %c.%s", 'A' + i, tmp.deviceName);
		gotoxy(49, 6 + (5 * j));
		printf("%s | %c.%s", st, 'A' + i + 1, tmp2.deviceName);
		gotoxy(101, 6 + (5 * j));
		printf("%s | ", st2);
		gotoxy(3, 7 + (5 * j));
		printf("|                                                    |                                                   |");
		gotoxy(3, 8 + (5 * j));
		printf("|                                                    |                                                   |");
		gotoxy(3, 9 + (5 * j));
		printf("|                                                    |                                                   |");
		gotoxy(3, 10 + (5 * j));
		printf("+--------------------------------------------------------------------------------------------------------+");
		i = i + 1;
		strcpy(st, "");
		strcpy(st2, "");
		j = j + 1;
	}
	printf("\n 장치설정은 해당 장치의 알파벳을 / ON/OFF기능을 원하시면 알파벳 'O'를 / ESC키를 누르시면 프로그램이 종료 됩니다.  ");
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}