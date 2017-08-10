#pragma once
#include "Structure.h"

void deviceMemcpy(void *p1, void *p2);
void devicePrint(void *p);
int deviceNameCmp(void *p1, void *p2);

void reserveMemcpy(void *p1, void *p2);
void reservePrint(void *p);
int reserveNameCmp(void *p1, void *p2);

void statusMemcpy(void *p1, void *p2);
int statusNameCmp(void *p1, void *p2);

void environMemcpy(void *p1, void *p2);
