#include <stdio.h>
#include <string.h>
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