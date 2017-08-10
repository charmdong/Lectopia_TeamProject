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