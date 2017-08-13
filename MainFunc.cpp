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
#define LAUNDRY 4
#define TEMPER 5
#define ESC 27

const char *setAirCondList[] = { "�� �� �� ��","�� �� �� ��","ǳ �� �� ��","���ư���(ESC)" };
const char *setAircCondModeList[] = { "��    ǳ","��    ǳ","��    ǳ","�� �� ǳ" };
const char *setTemperList[] = { "�� �� �� ��","���ư���(ESC)" };
const char *setCookList[] = { "�� �� �� ��","�� �� �� ��" };
const char *setLaundList[] = { "�� �� �� ��","�� �� �� ��" }; // ��Ź�� ����û���� ���� ���
const char *setLaundModeList[] = { "�� �� �� ��","�� �� �� ��","�� �� Ż ��" };
const char *setAirCleanerTimeReserveList[] = { "�� �� �� ��","�� �� �� ��" };
const char *setAirCleanerModeListp[] = { "�� �� �� ��","�� �� �� ��" };
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
			case 'O': 
				system("cls");
				printf("\n\n\t\t\t\t# ON / OFF �� ��ġ�� �ش��ϴ� ��ȣ�� �����ּ��� #\n");
				power(&list[2]);
				system("cls");
				break;
			case 'C': 
				system("cls");
				cookMenu(&list[2], &list[1]);
				system("cls");
				break;
			case 'E': 
				system("cls");
				laundMenu(&list[2], &list[1]);
				system("cls");
				break;
			case 'F':
				system("cls");
				temperMenu(&list[2]);
				system("cls");
				break;
			}
		}
		executeReserve(&list[1], &list[2]);
		printMain(&list[2]);
	}
	
	for (i = 0; i < 3; i++)
		fileWrite(&list[i], fileName[i]);
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

	fclose(fp);
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

	fclose(fp);
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

	fclose(fp);
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
		fscanf(fp, "%d ", &tmp.clean);
		addLast(elist, &tmp, sizeof(Environ), environMemcpy);
	}

	fclose(fp);
}

void fileWrite(List *list, const char *fileName)
{
	if (!strcmp("Device.txt", fileName))
		deviceWrite(list, fileName);
	else if (!strcmp("Reserve.txt", fileName))
		reserveWrite(list, fileName);
	else if (!strcmp("Status.txt", fileName))
		statusWrite(list, fileName);
	else {
		printf("Cannot find the File !\n");
		return;
	}
}

void deviceWrite(List *dlist, const char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	Node *cur;
	Device *tmp;

	sprintf(realFile, "%s%s", "C:/Data/", fileName);

	fp = fopen(realFile, "w");
	assert(fp != NULL);

	if (dlist->head->next == dlist->tail) {
		fprintf(fp, "");
		fclose(fp);
		return;
	}

	cur = dlist->head->next;
	while (cur != dlist->tail) {
		tmp = (Device *)(cur + 1);
		fprintf(fp, "%s\n%s\n%s\n%d\n", tmp->deviceName, tmp->company, tmp->indate, tmp->reserCnt);
		cur = cur->next;
	}
	fclose(fp);
}

void reserveWrite(List *rlist, const char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	Node *cur;
	Reserve *tmp;

	sprintf(realFile, "%s%s", "C:/Data/", fileName);

	fp = fopen(realFile, "w");
	assert(fp != NULL);

	if (rlist->head->next == rlist->tail) {
		fprintf(fp, "");
		fclose(fp);
		return;
	}

	cur = rlist->head->next;
	while (cur != rlist->tail) {
		tmp = (Reserve *)(cur + 1);
		fprintf(fp, "%s\n%d\n%d\n%d\n%d\n", tmp->deviceName, tmp->hour, tmp->min, tmp->reStatus, tmp->mode);
		cur = cur->next;
	}
	fclose(fp);
}

void statusWrite(List *slist, const char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	Node *cur;
	Status *tmp;

	sprintf(realFile, "%s%s", "C:/Data/", fileName);

	fp = fopen(realFile, "w");
	assert(fp != NULL);

	if (slist->head->next == slist->tail) {
		fprintf(fp, "");
		fclose(fp);
		return;
	}

	cur = slist->head->next;
	while (cur != slist->tail) {
		tmp = (Status *)(cur + 1);
		fprintf(fp, "%s\n%d\n%d\n%d\n", tmp->deviceName, tmp->status, tmp->mode, tmp->temper);
		cur = cur->next;
	}
	fclose(fp);
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
				powerCheck(slist, LAUNDRY);
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
		printf("\n\n\t\t\t\t\t    ��ϵ��� ���� ��ġ�Դϴ�\n");
		return;
	}
	
	s = ((Status *)(cur + 1));

	if (s->status) {
		printf("\n\n\t\t\t\t\t%11s ��(��) OFF �մϴ�\n", s->deviceName);
		s->status = 0;
	}
	else {
		printf("\n\n\t\t\t\t\t%11s ��(��) ON �մϴ�\n", s->deviceName);
		s->status = 1;
	}
}

void printMain(List *slist)
{
	Node *cur , *cur2;
	char st[10] = { " " };
	char st2[10] = { " " };
	int i = 0;
	int j = 0;
	gotoxy(3, 5);
	printf("+--------------------------------------------------------------------------------------------------------+");
	for (i = 0; i<5; i++)
	{
		cur = slist->head->next;
		while (cur != slist->tail) {
			if (statusNameCmp(cur + 1, deviceName[i])){
				if (((Status*)(cur+1))->status == 1)
					strcpy(st, "    ��");
				else
					strcpy(st, "    ��");
				break;
			}
			cur = cur->next;
		}
		if (!strcmp(st, ""))
			strcpy(st, "�̵��");

		cur2 = slist->head->next;
		while (cur2 != slist->tail){
			if (statusNameCmp(cur2 + 1, deviceName[i+1])){
				if (((Status*)(cur2 + 1))->status == 1)
					strcpy(st2, "    ��");
				else
					strcpy(st2, "    ��");
				break;
			}
			cur2 = cur2->next;
		}
		if (!strcmp(st2, ""))
			strcpy(st2, "�̵��");
		
		gotoxy(3, 6 + (5 * j));
		printf("| %c.%s", 'A' + i, deviceName[i]);
		gotoxy(49, 6 + (5 * j));
		printf("%s | %c.%s", st, 'A' + i + 1, deviceName[i+1]);
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
		i++;
		strcpy(st, "");
		strcpy(st2, "");
		j++;
	}
	printf("\n ��ġ������ �ش� ��ġ�� ���ĺ��� / ON/OFF����� ���Ͻø� ���ĺ� 'O'�� / ESCŰ�� �����ø� ���α׷��� ���� �˴ϴ�.  ");
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
/*
int Mode(char *device)
{
	int mode;
	if (!strcmp(device, deviceName[AIRCOND])) {
		printf("Select Mode >> ");
		while (1) {
			scanf("%d", &mode);
			if (mode >= 1 && mode <= 4)
				return mode;
		}
	}
	else if(!strcmp(device, deviceName[AIRCLEANER])){
		printf("Select Mode >> ");
		while (1) {
			scanf("%d", &mode);
			if (mode >= 1 && mode <= 3)
				return mode;
		}
	}
	else {
		printf("Select Mode >> ");
		while (1) {
			scanf("%d", &mode);
			if (mode == 1 || mode == 2)
				return mode;
		}
	}
}*/
int Mode(char *device)
{
	system("cls");
	int mode;
	if (!strcmp(device, deviceName[AIRCOND])) {
		while (1) {
			//myflush();
			mode = menu(setAircCondModeList, sizeof(setAircCondModeList) / sizeof(setAircCondModeList[0]));
			mode = mode - '0';
			printf("mode = %d", mode);
			if (mode >= 1 && mode <= 4)
				return mode;
		}
	}
	else if (!strcmp(device, deviceName[AIRCLEANER])) {
		while (1) {
			//myflush();
			mode = menu(setAirCleanerModeListp, sizeof(setAirCleanerModeListp) / sizeof(setAirCleanerModeListp[0]));
			mode = mode - '0';
			if (mode >= 1 && mode <= 2)
				return mode;
		}
	}
	else {
		while (1) {
			mode = menu(setLaundModeList, sizeof(setLaundModeList) / sizeof(setLaundModeList[0]));
			mode = mode - '0';
			if (mode >= 1 && mode <= 4)
				return mode;
		}
	}
}
void executeReserve(List *rlist, List *slist)
{
	Node *cur, *scur;
	List *check;
	
	if (rlist->head->next == rlist->tail)
		return;

	check = (List *)calloc(1, sizeof(List));
	createList(check);

	reserveCheck(rlist, check);
	
	cur = check->head->next;
	while (cur != check->tail) {
		removeNode(rlist, cur + 1, reserveCmp);
		scur = searchNode(slist, ((Reserve *)(cur + 1))->deviceName, statusNameCmp);
		changeStatus(slist, ((Status*)(scur + 1)), ((Reserve *)(cur + 1)));
		cur = cur->next;
	}
	
	reserveWrite(rlist, "Reserve.txt");
	destroyList(check);
	free(check);
}

void reserveCheck(List *rlist, List *check)
{
	Node *cur;
	Reserve res;
	time_t tmp;
	tm *nowTime;
	tmp = time(NULL);
	nowTime = localtime(&tmp);

	cur = rlist->head->next;
	while (cur != rlist->tail) {
		if (reserveTimeCmp(cur + 1, nowTime) != 1) 
			addLast(check, cur+1, sizeof(Reserve), reserveMemcpy);
		cur = cur->next;
	}
}

void changeStatus(List *slist, Status *scur, Reserve *rcur)
{
	scur->status = rcur->reStatus;

	if (!strcmp(rcur->deviceName, deviceName[AIRCOND]) 
		|| !strcmp(rcur->deviceName, deviceName[AIRCLEANER])
		|| !strcmp(rcur->deviceName, deviceName[LAUNDRY])) {
		scur->mode = rcur->mode;
	}
}

//========================================//

void temperMenu(List *slist)
{
	Node *cur;
	char choice;

	if ((cur = searchNode(slist, deviceName[TEMPER], statusNameCmp)) == NULL) {
		printf("��ġ�� ��ϵǾ� ���� �ʽ��ϴ�. ���� �޴��� ���ư��ϴ�.\n");
		return;
	}
	setTemper(slist, ((Status *)(cur+1)));
}

void setTemper(List *slist, Status *scur)
{
	int tempr;
	while (1) {
		char c = menu(setTemperList, sizeof(setTemperList) / sizeof(setTemperList[0]));
		if (c == '1') {
			system("cls");
			gotoxy(12, 3);
			printf("============<���� ����>=============");
			gotoxy(12, 4);
			printf("# ���ϴ� ������ �Է����ּ���(10~50��) #");
			while (1) {
				gotoxy(12, 8);
				printf("** ���� >> ");
				if (scanf("%d", &tempr) != 1 || tempr < 10 || tempr>50) {
					myflush();
					gotoxy(22, 8);
					printf("                                       ");
					gotoxy(12, 9);
					printf("+ �ش� �µ��� ������ �Ұ����մϴ� +\n");
				}
				else break;
				Sleep(700);
				gotoxy(12, 9);
				printf("                                            ");
			}
			scur->temper = tempr;
			gotoxy(12, 12);
			printf("+ ������ %d�� �����Ǿ����ϴ� +\n", tempr);
			Sleep(700);
			system("cls");
		}
		else if (c == 'r')
			return;
		else
			continue;
	}
}

char kbhitMenu() // ��ư ������ �� ���·� ����.
{
	while (1) {
		if (kbhit())
		{
			char c = getch();
			if (c == 27)
				return 'r';
			else if (c >= 'A' && c <= 'Z')
				c += 32;
			return c;
		}
	}
}

int menu(const char **mList, size_t menuCnt) // �μ� �޴� ��� �Լ�.
{
	size_t menuNum = 0;   /* �������� �ʴ� �޴� ��ȣ ���� */
	size_t i;

	gotoxy(12, 3);
	printf("+---------------+");
	for (i = 0; i < menuCnt; i++) {   /* �޴� ��� */
		gotoxy(12, 4 + i);
		printf("%d. %s\n", i + 1, mList[i]);
	}
	gotoxy(12, 4 + i);
	printf("+---------------+");
	gotoxy(12, 5 + i);
	while (menuNum<1 || menuNum>menuCnt) {   /* �޴���ȣ�� ��ȿ���� ���� ���� �ݺ� */
		printf("# ���� : ");
		return kbhitMenu();
	}
}

void myflush()
{
	while (getchar() != '\n');
}

void cookMenu(List *slist, List *rlist)
{
	Node *cur;
	
	if ((cur = searchNode(slist, deviceName[COOK], statusNameCmp)) == NULL) {
		printf("��ġ�� ��ϵǾ� ���� �ʽ��ϴ�. ���� �޴��� ���ư��ϴ�.\n");
		Sleep(700);
		return;
	}
	setCook(slist, rlist);
}

void setCook(List *slist, List *rlist)
{
	char c;
	while (1) {
		c = menu(setCookList, sizeof(setCookList) / sizeof(setCookList[0]));
		system("cls");
		if (c == '1')
			timeReserve(rlist, deviceName[COOK]);
		else if (c == '2') {
			powerCheck(slist, COOK);
			Sleep(700);
			system("cls");
		}
		else if (c == 'r') return;
		else continue;
	}
}

void timeReserve(List *rlist, char *device)
{
	Reserve tmp;
	reserveInit(&tmp);

	system("cls");
	gotoxy(12, 3);
	printf("------------<�ð� ����>-------------");
	gotoxy(12, 4);
	printf(": ������ �ð��� �Է����ּ��� (24h) :");
	gotoxy(12, 5);
	printf("------------------------------------");

	while (1) {
		gotoxy(12, 8);
		printf("** �� >> ");
		if (scanf("%d", &tmp.hour) != 1 || tmp.hour < 0 || tmp.hour>24) {
			gotoxy(12, 10);
			printf("+ �ش� �ð��� ������ �Ұ��մϴ� +\n");
			myflush();
		}
		else break;
		Sleep(700);
		gotoxy(20, 8);
		printf("                                            ");
		gotoxy(12, 10);
		printf("                                            ");
	}
	while (1) {
		gotoxy(12, 9);
		printf("** �� >> ");
		if (scanf("%d", &tmp.min) != 1 || tmp.min < 0 || tmp.min>60) {
			gotoxy(12, 10);
			printf("+ �ش� �ð��� ������ �Ұ��մϴ� +");
			myflush();
		}
		else break;
		Sleep(700);
		gotoxy(20, 9);
		printf("                                            ");
		gotoxy(12, 10);
		printf("                                            ");
	}
	if (!strcmp(device, deviceName[AIRCOND])
		|| !strcmp(device, deviceName[AIRCLEANER])
		|| !strcmp(device, deviceName[LAUNDRY])) {
		while (1) {
			gotoxy(12, 10);
			printf("** ��� >> ");
			if (scanf("%d", &tmp.mode) != 1 || tmp.mode <= 0 || tmp.mode > 4) {
				gotoxy(12, 10);
				printf("+ �ش� �ð��� ������ �Ұ��մϴ� +");
				myflush();
			}
			else break;
			Sleep(700);
			gotoxy(20, 9);
			printf("                                            ");
			gotoxy(12, 10);
			printf("                                            ");
		}
		gotoxy(12, 13);
		printf("+ %d�� %d�п� %d ���� ������ �Ϸ�Ǿ����ϴ� +\n", tmp.hour, tmp.min, tmp.mode);
		Sleep(1000);
		system("cls");
	}
	else {
		gotoxy(12, 13);
		printf("+ %d�� %d�п� ������ �Ϸ�Ǿ����ϴ� +\n", tmp.hour, tmp.min);
		Sleep(700);
		system("cls");
	}
	strcpy(tmp.deviceName, device);
	tmp.reStatus = 1;	// �����ؾ���
	addLast(rlist, &tmp, sizeof(Reserve), reserveMemcpy);
	return;
}

void laundMenu(List *slist, List *rlist)
{
	char n;
	Node *cur;
	
	if ((cur = searchNode(slist, deviceName[LAUNDRY], statusNameCmp)) == NULL) {
		printf("��ϵ��� ���� ��ġ�Դϴ�\n");
		return;
	}

	while (1) {
		n = menu(setLaundList, sizeof(setLaundList) / sizeof(setLaundList[0]));
		if (n == '1') {
			timeReserve(rlist, deviceName[LAUNDRY]);
		}
		else if (n == '2') {
			((Status*)(cur + 1))->mode = Mode(deviceName[LAUNDRY]);
		}
		else if (n == 'r')
			return;
		continue;
	}
}
/*
void laundMenu(List *slist)
{
	Node *cur;
	Status temp;
	statusInit(&temp);
	strcpy(temp.deviceName, deviceName[LAUNDRY]);
	cur = slist->head->next;
	while (cur != slist->tail) {
		if (statusNameCmp(cur + 1, &temp) == 1)
			break;
		else if (cur->next == slist->tail) {
			printf("��ġ�� ��ϵǾ� ���� �ʽ��ϴ�. ���� �޴��� ���ư��ϴ�.\n");
			getch();
			return;
		}
		cur = cur->next;
	}
	setLaund();

}
void aircleanMenu(List *slist)
{
	Node *cur;
	Status temp;
	statusInit(&temp);
	strcpy(temp.deviceName, deviceName[AIRCLEANER]);
	cur = slist->head->next;
	while (cur != slist->tail) {
		if (statusNameCmp(cur + 1, &temp) == 1)
			break;
		else if (cur->next == slist->tail) {
			printf("��ġ�� ��ϵǾ� ���� �ʽ��ϴ�. ���� �޴��� ���ư��ϴ�.\n");
			getch();
			return;
		}
		cur = cur->next;
	}
	setAirCleaner();
}


void setAirCondTemper()
{
	int tempr;
	system("cls");
	gotoxy(12, 3);
	printf("---------------<�µ� ����>---------------");
	gotoxy(12, 4);
	printf(": ���ϴ� �µ��� �Է����ּ��� (18~30��)  :");
	gotoxy(12, 5);
	printf("-----------------------------------------");
	while (1) {
		gotoxy(12, 8);
		printf("�µ� >> ");
		if (scanf("%d", &tempr) != 1 || tempr < 18 || tempr>30) {
			gotoxy(12, 9);
			printf("+ �ش� �µ��� ������ �� �����ϴ�. +");
		}
		else break;
	}
	gotoxy(12, 12);
	printf("+ ������ ���� �µ��� %d���� ����Ǿ����ϴ�. +\n", tempr);

	return;
}
void setAircCondMode()
{

	int windNum = menu(setAircCondModeList, sizeof(setAircCondModeList) / sizeof(setAircCondModeList[0]));
	system("cls");
	if (windNum == 1)
		printf("\n\n\n+ ������ ǳ���� ��ǳ���� ����Ǿ����ϴ�. +\n\n\n");
	else if (windNum == 2)
		printf("\n\n\n+ ������ ǳ���� ��ǳ���� ����Ǿ����ϴ�. +\n\n\n");
	else if (windNum == 3)
		printf("\n\n\n+ ������ ǳ���� ��ǳ���� ����Ǿ����ϴ�. +\n\n\n");
	else
		printf("\n\n\n+ ������ ǳ���� �ڿ�ǳ���� ����Ǿ����ϴ�. +\n\n\n");

	return;
}

void setLaund()
{
	int error = -1;
	char mode;
	char c = menu(setLaundList, sizeof(setLaundList) / sizeof(setLaundList[0]));
	system("cls");
	if (c == '1')
		setTime();
	else if (c == '2') {
		mode = menu(setLaundModeList, sizeof(setLaundModeList) / sizeof(setLaundModeList[0]));
		while (1) {
			if (mode != '1' && mode != '2' && mode != '3') {
				gotoxy(20, 8);
				printf("                                      ");
				gotoxy(2, 10);
				printf("### �ùٸ� ���� �Է��Ͻÿ�.(1 ~ 3) ###\n");
				gotoxy(43, 10);
				if (scanf("%d", &error) != 1 && error != 1 && error != 2 && error != 3)
					myflush();
				else if (error == 1 || error == 2 || error == 3)
					break;
				gotoxy(43, 10);
				printf("                                  ");
			}
			else break;
		}
		system("cls");
		gotoxy(10, 5);
		if (mode == '1' || error == 1)
			printf("+ �⺻���� ���۵˴ϴ�. +\n\n\n");
		else if (mode == '2' || error == 2)
			printf("+ ��Ӹ��� ���۵˴ϴ�. +\n\n\n");
		else if (mode == '3' || error == 3)
			printf("+ ��� �� Ż���� ���۵˴ϴ�. +\n\n\n");

		return;
	}
}
void setAirCleaner()
{
	int error = -1;
	char mode;
	char c = menu(setLaundList, sizeof(setLaundList) / sizeof(setLaundList[0]));
	system("cls");
	if (c == '1') {
		menu(setAirCleanerTimeReserveList, sizeof(setAirCleanerTimeReserveList) / sizeof(setAirCleanerTimeReserveList[0]));
		setTime();
	}
	else if (c == '2') {
		mode = menu(setAirCleanerModeListp, sizeof(setAirCleanerModeListp) / sizeof(setAirCleanerModeListp[0]));
		while (1) {
			if (mode != '1' && mode != '2') {
				gotoxy(20, 7);
				printf("                                      ");
				gotoxy(2, 10);
				printf("### �ùٸ� ���� �Է��Ͻÿ�.(1 ~ 2) ###\n");
				gotoxy(43, 10);
				if (scanf("%d", &error) != 1 && error != 1 && error != 2)
					myflush();
				else if (error == 1 || error == 2)
					break;
				gotoxy(43, 10);
				printf("                                  ");
			}
			else break;
		}
		system("cls");
		gotoxy(10, 5);
		if (mode == '1' || error == 1)
			printf("+ ���Ӹ��� ���۵˴ϴ�. +\n\n\n");
		else if (mode == '2' || error == 2)
			printf("+ ��Ӹ��� ���۵˴ϴ�. +\n\n\n");

		return;
	}
}*/