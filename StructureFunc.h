#pragma once
#include "Structure.h"

void deviceMemcpy(void *p1, void *p2);
void devicePrint(void *p);
int deviceNameCmp(void *p1, void *p2);

void reserveMemcpy(void *p1, void *p2);
void reservePrint(void *p);
int reserveNameCmp(void *p1, void *p2);
int reserveTimeCmp(void *p1, void *p2);
/*
return : -1 => 예약 시간 지남
			  0 => 예약 시간
			  1 => 예약 시간 전
p1 : Reserve 타입 변수의 주소
p2 : tm 타입 변수의 주소 (tm은 time.h에서 선언되어 있는 구조체)
*/

void statusMemcpy(void *p1, void *p2);
int statusNameCmp(void *p1, void *p2);

void environMemcpy(void *p1, void *p2);

int createList(List *lp);					/* 연결 리스트 초기화 */
void destroyList(List *lp);
int addLast(List *lp, void *data, size_t size, void(*memcpy)(void *, void *));			/* tail node 앞에 node 추가(정순 저장) */
void displayList(List *lp, void(*dataPrint)(void*));					/* 리스트 내의 모든 데이터 출력 */
Node * searchNode(List *lp, void* data, int(*dataCompare)(void*, void*));
int removeNode(List *lp, void* data, int(*dataCompare)(void *, void *));
