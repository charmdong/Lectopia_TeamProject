#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "Structure.h"
#include "StructFunc.h"
#include "MainFunc.h"

void deviceMemcpy(void *p1, void *p2)
{
	Device *val1 = (Device *)p1, *val2 = (Device *)p2;

	strcpy(val1->deviceName, val2->deviceName);
	strcpy(val1->company, val2->company);
	strcpy(val1->indate, val2->indate);
	val1->reserCnt = val2->reserCnt;
}

void devicePrint(void *p)
{
	Device *val = (Device *)p;
	printf("장치명 : %s\n", val->deviceName);
	printf("제조 정보 : %s\n", val->company);
	printf("등록 일자 : %s\n", val->indate);
}

int deviceNameCmp(void *p1, void *p2)
{
	Device *val1 = (Device *)p1, *val2 = (Device *)p2;
	if (!strcmp(val1->deviceName, val2->deviceName))
		return 1;
	return 0;
}

void deviceInit(void *p)
{
	Device *val = (Device *)p;
	strcpy(val->deviceName, "");
	strcpy(val->company, "");
	strcpy(val->indate, "");
	val->reserCnt = 0;
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
	if (val->reStatus == 1)
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

void reserveInit(void *p)
{
	Reserve *val = (Reserve *)p;
	strcpy(val->deviceName, "");
	val->hour = val->min = val->reStatus = -1;
	val->mode = 0;
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
	Status *val1 = (Status *)p1;
	char *device = (char*)p2;

	if (!strcmp(val1->deviceName, device))
		return 1;
	return 0;
}

void statusInit(void *p)
{
	Status *val = (Status *)p;
	strcpy(val->deviceName, "");
	val->status = -1;
	val->mode = 0;
	val->temper = 23;
}
//===============================================//
void environMemcpy(void *p1, void *p2)
{
	Environ *val1 = (Environ *)p1, *val2 = (Environ *)p2;

	val1->nowTemper = val2->nowTemper;
	val1->clean = val2->clean;
}

void environInit(void *p)
{
	((Environ *)p)->nowTemper = ((Environ *)p)->clean = 0;
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

//=============================================//