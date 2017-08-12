#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "func.h"
#include "StructureFunc.h"

const char *fileName[] = { "Device.txt", "Reserve.txt", "Status.txt", "Environ.txt", "Info.txt" };
const char *deviceName[] = { "AIRCOND", "AIRCLEANER", "COOK", "INDUCTION", "LAUND", "TEMPER" };

void fileRead(List *list, const char *fileName)
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
			fscanf(fp, "%d", &tmp.reserCnt);
			fscanf(fp, "%c", &nl);
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
		fscanf(fp, "%d", &tmp.mode);
		fscanf(fp, "%c", &nl);
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
		fscanf(fp, "%d", &tmp.temper);
		fscanf(fp, "%c", &nl);
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

	while (fscanf(fp, "%d", &tmp.nowTemper)) {
		fscanf(fp, "%d", &tmp.clean);
		addLast(elist, &tmp, sizeof(Environ), environMemcpy);
	}
}

void power(List *slist)
{
	char choice;
	int res;
	Node *cur;
	Status tmp;
	statusInit(&tmp);

	while (1) {
		if (kbhit()) {
			choice = getch();
			if (choice >= 97 && choice <= 122)
				choice -= 32;
			switch (choice) {
			case 'A':
				powerCheck(slist, &tmp, 0);
				break;
			case 'B':
				powerCheck(slist, &tmp, 1);
				break;
			case 'C':
				powerCheck(slist, &tmp, 2);
				break;
			case 'D':
				powerCheck(slist, &tmp, 3);
				break;
			case 'E':
				powerCheck(slist, &tmp, 4);
				break;
			case 'F':
				powerCheck(slist, &tmp, 5);
				break;
			default: printf("Wrong selection !\n");
			}
		}
		//printMain(slist);
	}
}

void powerCheck(List *slist, Status *s, int index)
{
	Node *cur;
	strcpy(s->deviceName, deviceName[index]);
	if ((cur = searchNode(slist, s, statusNameCmp)) == NULL)
		printf("등록되어 있지 않은 장치입니다!\n");
	else {
		statusMemcpy(cur + 1, s);
		if (s->status) {
			printf("%s를 OFF합니다.\n", s->deviceName);
			s->status = 0;
			statusMemcpy(s, cur + 1);
		}
		else {
			printf("%s를 ON합니다.\n", s->deviceName);
			s->status = 1;
			statusMemcpy(s, cur + 1);
		}
	}
}
