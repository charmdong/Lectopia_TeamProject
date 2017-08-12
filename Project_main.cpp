#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "func.h"
#include "StructureFunc.h"

char *fileName[] = { "Device.txt", "Reserve.txt", "Status.txt", "Environ.txt", "Info.txt" };

int main()
{
	List test;
	createList(&test);
	fileRead(&test, "Device.txt");
	return 0;
}

void fileRead(List *list, char *fileName)
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

void deviceRead(List *dlist ,char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	char nl;
	Device tmp;

	sprintf(realFile, "%s%s", "C:/Data/", fileName);

	fp = fopen(realFile, "rt");
	assert(fp != NULL);
	
	if (!strcmp("Device.txt", fileName)) {
		while (!fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
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
		while (!fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
			tmp.deviceName[strlen(tmp.deviceName) - 1] = '\0';
			fgets(tmp.company, sizeof(tmp.company), fp);
			tmp.company[strlen(tmp.company) - 1] = '\0';
			addLast(dlist, &tmp, sizeof(Device), deviceMemcpy);
		}
	}
}

void reserveRead(List *rlist, char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	char nl;
	Reserve tmp;

	sprintf(realFile, "%s%s", "C:/Data", fileName);

	fp = fopen(realFile, "rt");
	if (fp == NULL) return;

	while (!fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
		tmp.deviceName[strlen(tmp.deviceName) - 1] = '\0';
		fscanf(fp, "%d", &tmp.hour);
		fscanf(fp, "%d", &tmp.min);
		fscanf(fp, "%d", &tmp.reStatus);
		fscanf(fp, "%d", &tmp.mode);
		fscanf(fp, "%c", &nl);
		addLast(rlist, &tmp, sizeof(Reserve), reserveMemcpy);
	}
}

void statusRead(List *slist, char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	char nl;
	Status tmp;

	sprintf(realFile, "%s%s", "C:/Data", fileName);

	fp = fopen(realFile, "rt");
	if(fp == NULL) return;

	while (!fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
		fscanf(fp, "%d", &tmp.status);
		fscanf(fp, "%d", &tmp.mode);
		fscanf(fp, "%d", &tmp.temper);
		fscanf(fp, "%c", &nl);
		addLast(slist, &tmp, sizeof(Status), statusMemcpy);
	}
}

void environRead(List *elist,char *fileName)
{
	FILE *fp;
	char realFile[FILENAME_MAX];
	char nl;
	Environ tmp;

	sprintf(realFile, "%s%s", "C:/Data", fileName);

	fp = fopen(realFile, "rt");
	if (fp == NULL) return;

	while (fscanf(fp, "%d", &tmp.nowTemper)) {
		fscanf(fp, "%d", &tmp.clean);
		addLast(elist, &tmp, sizeof(Environ), environMemcpy);
	}
}

void mainMeu()
{
	List list[4];
	int i;

	for (i = 0; i < sizeof(list) / sizeof(list[0]); i++){
		createList(&list[i]);
		fileRead(&list[i], fileName[i]);
	}
}