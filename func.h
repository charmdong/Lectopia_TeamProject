#pragma once
#include "Structure.h"
#define FILE_NAME 30

/*
list : List �� 3��¥�� �迭��
dlist : Node�� Device ����ü�� �����Ǿ�, �� ��ġ���� ������ ���� List
rlist : Node�� Reserve ����ü�� �����Ǿ�, �� ��ġ���� ���� ������ ���� List
slist : Node�� Status ����ü�� �����Ǿ�, �� ��ġ���� ���� ������ ���� List
*/

void fileRead(List *list, char *fileName);	// fileName�� �ش��ϴ� ������ ������ �ش��ϴ� List�� ���� 
void deviceRead(List *dlist, char *fileName);
void reserveRead(List *rlist,char *fileName);
void statusRead(List *slist,char *fileName);
void environRead(List *elist,char *filName);
void fileWrite(List *list, char *fileName);	// list�� ������ �ش� ���Ͽ� �����Ѵ�
void mainMenu();	// Main �޴����� ���.
void gotoxy(int, int);
void printMain(List *slist);

void setMenu(List *list);				// ��������� �޴�. 
void enrollDevice(List *dlist);		// ��ġ�� ����ϱ� ���� �Լ�
void freeDevice(List *list);			// ��ġ�� �����ϱ� ���� �Լ�
void infoDevice(List *dlist);			// ��ġ���� ������ ������ִ� �Լ�
void checkRes(List *rlist);			// ��ġ���� ���� ������ ������ִ� �Լ�
void resetAll(List *list);				// ��� ��ġ, ����, ������ ������ �����ϴ� �Լ�

void power(List *slist);				// cookmenu 2��, ���θ޴��Լ����� 'O' �Է� �� ȣ��
												// ��ġ���� ON, OFF�� �����ϴ� �Լ�
void printStatus(List *slist);			// ���� ��ġ���� ���¸� ������ִ� �Լ�

void airMenu(List *list);				// ������ �޴��� �����ϴ� �Լ�
int airTemp();							// ������ ��� �µ� �� ����

void temperMenu(List *slist);		// ���� ���� �޴��� �����ϴ� �Լ�
int waterTemp();						// ���� ��� �µ� �� ��ȯ���ִ� �Լ�

void cookMenu(List *list);			// ��� ���� �޴��� �����ϴ� �Լ�

void laundMenu(List *list);			// ��Ź�� ���� �޴��� �����ϴ� �Լ�
int Mode();	// ��� ��Ź�� �� ����û���� ��� ��ȣ ��ȯ�ϴ� �Լ�
					// ��Ź���� ��� 1~3�� �� �ϳ�, ����û������ ��� 1 or 2 �� �ϳ� ��ȯ
void aircleanMenu(List *list);		// ����û���� ���� �޴��� �����ϴ� �Լ�

void timeReserve(List *rlist);		// �ð� ������ ���� �Լ�
												// ��� ��ġ �޴����� ��� ����
