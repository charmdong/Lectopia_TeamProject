#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
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
const char *deviceName[] = { "AIRCOND", "AIRCLEANER", "COOK", "INDUCTION", "LAUND", "TEMPER" };

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
			default: printf("Wrong Selection ! \n");
			}
		}
	}
}

void powerCheck(List *slist, int index)
{
	Node *cur;
	Status tmp;
	statusInit(&tmp);

	strcpy(tmp.deviceName, deviceName[index]);
	
	if ((cur = searchNode(slist, &tmp, statusNameCmp)) == NULL) {
		printf("등록되지 않은 장치입니다 !\n");
		return;
	}
	
	statusMemcpy(&tmp, cur + 1);	// 임시 구조체 변수에 해당 장치 상태 정보 저장
	if (tmp.status) {
		printf("%s 를 OFF 합니다.\n", tmp.deviceName);
		tmp.status = 0;
		statusMemcpy(cur + 1, &tmp);
	}
	else {
		printf("%s 를 ON 합니다.\n", tmp.deviceName);
		tmp.status = 1;
		statusMemcpy(cur + 1, &tmp);
	}
}