#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "Structure.h"
#include "StructureFunc.h"

void deviceMemcpy(void *p1, void *p2)
{
	Device *val1 = (Device *)p1, *val2 = (Device *)p2;

	strcpy(val1->deviceName, val2->deviceName);
	strcpy(val1->company, val2->company);
	strcpy(val1->conductNum, val2->conductNum);
	strcpy(val1->indate, val2->indate);
	val1->reserCnt = val2->reserCnt;
}

void devicePrint(void *p)
{
	Device *val = (Device *)p;
	printf("장치명 : %s\n", val->deviceName);
	printf("제조 회사 : %s\n", val->company);
	printf("제품 번호 : %s\n", val->conductNum);
	printf("등록 일자 : %s\n", val->indate);
}

int deviceNameCmp(void *p1, void *p2)
{
	Device *val1 = (Device *)p1, *val2 = (Device *)p2;
	if (!strcmp(val1->deviceName, val2->deviceName))
		return 1;
	return 0;
}

//==============================================//
void reserveMemcpy(void *p1, void *p2)
{
	Reserve *val1 = (Reserve *)p1, *val2 = (Reserve *)p2;

	strcpy(val1->deviceName, val2->deviceName);
	val1->hour = val2->hour;
	val1->min = val2->min;
	val1->reStatus = val2->reStatus;
	val1->mode = val2->mode;
}
void reservePrint(void *p)
{
	Reserve * val = (Reserve *)p;

	printf("장치명 = %s\n", val->deviceName);
	printf("시 = %d\n", val->hour);
	printf("분 = %d\n", val->min);
	if (val->reStatus == -1)
		printf("ON 예약\n");
	else
		printf("OFF 예약\n");
	if (!strcmp(val->deviceName, "AIRCOND")) {      //   에어컨
		if (val->mode == 1)
			printf("모드 : 강풍\n");
		else if (val->mode == 2)
			printf("모드 : 약풍\n");
		else if (val->mode == 3)
			printf("모드 : 미풍\n");
		else
			printf("모드 : 자연풍\n");
	}
	else if (!strcmp(val->deviceName, "LAUNDRY")) {  //   세탁기
		if (val->mode == 1)
			printf("모드 : 기본\n");
		else if (val->mode == 2)
			printf("모드 : 쾌속\n");
		else
			printf("모드 : 헹굼탈수\n");
	}
	else {                                 //   공기청정기
		if (val->mode == 1)
			printf("모드 : 저속\n");
		else
			printf("모드 : 고속\n");
	}
}

int reserveNameCmp(void *p1, void *p2) //같으면 1
{
	Reserve *val1 = (Reserve *)p1, *val2 = (Reserve *)p2;

	if (!strcmp(val1->deviceName, val2->deviceName))
		return 1;
	else
		return 0;
}

int reserveTimeCmp(void *p1, void *p2)
{
	Reserve *val = (Reserve *)p1;
	tm *cur = (tm *)p2;

	if (val->hour < cur->tm_hour)
		return 1;
	else if (val->hour == cur->tm_hour) {
		if (val->min > cur->tm_min)
			return 1;
		else if (val->min == cur->tm_min)
			return 0;
		return -1;
	}
	return -1;
}

//==============================================//
void statusMemcpy(void *p1, void *p2)
{
	Status *val1 = (Status *)p1, *val2 = (Status *)p2;

	strcpy(val1->deviceName, val2->deviceName);
	val1->status = val2->status;
	val1->mode = val2->mode;
	val1->temper = val2->temper;
}

int statusNameCmp(void *p1, void *p2)
{
	Status *val1 = (Status *)p1, *val2 = (Status *)p2;
	if (!strcmp(val1->deviceName, val2->deviceName))
		return 1;
	return 0;
}

//===============================================//
void environMemcpy(void *p1, void *p2)
{
	Environ *val1 = (Environ *)p1, *val2 = (Environ *)p2;

	val1->nowTemper = val2->nowTemper;
	val1->clean = val2->clean;
}

//===============================================//
int createList(List *lp)
{
	if (lp == NULL) 
		return 0;
	lp->head = (Node*)malloc(sizeof(Node));
	if (lp->head == NULL) 
		return 0;
	
	lp->tail = (Node*)malloc(sizeof(Node));
	if (lp->tail == NULL) 
		return 0;

	lp->head->next = lp->tail;
	lp->tail->prev = lp->head;
	lp->head->prev = lp->head;
	lp->tail->next = lp->tail;
	return 1;
}

void destroyList(List *lp)
{
	Node *cur, *nextp;
	cur = lp->head->next;
	
	while (cur != lp->tail) {
		nextp = cur;
		free(cur);
		cur = nextp->next;
	}

	free(lp->head);
	free(lp->tail);
}

int addLast(List *lp, void *data, size_t size, void(*memcpy)(void *, void*))
{
	Node *np;
	
	if (lp == NULL) return 0;
	
	np = (Node*)malloc(sizeof(Node) + size);
	if (np == NULL) return 0;

	memcpy(np + 1, data);
	np->next = lp->tail;
	lp->tail->prev->next = np;
	np->prev = lp->tail->prev;
	lp->tail->prev = np;
	
	return 1;
}

void displayList(List *lp, void(*dataPrint)(void *))
{
	Node *cur;
	
	if (lp == NULL) return;

	cur = lp->head->next;

	while (cur != lp->tail) {
		dataPrint(cur + 1);
		cur = cur->next;
	}
	//printf("\n");
}

Node *searchNode(List *lp, void *data, int(*dataCompare)(void *, void*))
{
	Node *cur;

	if (lp == NULL) return NULL;

	cur = lp->head->next;

	while (cur != lp->tail) {
		if (dataCompare(cur + 1, data))
			return cur;
		cur = cur->next;
	}
	return NULL;
}

int removeNode(List *lp, void *data, int(*dataCompare)(void *, void*))
{
	Node *delp;

	if (lp == NULL) return 0;

	delp = searchNode(lp, data, dataCompare);
	if (delp == NULL) return 0;

	delp->prev->next = delp->next;
	delp->next->prev = delp->prev;
	free(delp);
	return 1;
}

List *reserveRead(char *fileName)
{
	FILE *fp;
	List rlist;
	char realFile[FILENAME_MAX];
	Reserve tmp;

	createList(&rlist);
	sprintf(realFile, "%s%s", "C:/Data", fileName);

	fp = fopen(realFile, "rt");
	if (fp == NULL)
		return NULL;

	while (!fgets(tmp.deviceName, sizeof(tmp.deviceName), fp)) {
		tmp.deviceName[strlen(tmp.deviceName) - 1] = '\0';
		fscanf(fp, "%d", &tmp.hour);
		fscanf(fp, "%d", &tmp.min);
		fscanf(fp, "%d", &tmp.reStatus);
		fscanf(fp, "%d", &tmp.mode);
		addLast(&rlist, &tmp, sizeof(Reserve), reserveMemcpy);
	}

	return &rlist;
}