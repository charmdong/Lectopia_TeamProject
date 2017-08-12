#pragma once
#define MAX_NAME 20
#define MAX_COND 30

/*		ȯ�� ���� ����ü
		nowTemper : �µ�
		clean : ���� û����
*/
typedef struct Environ {
	int nowTemper;
	int clean;
}Environ;

/*		��ġ ���� ����ü
		deviceName : ��ġ��
		status : ON - 1, OFF - 0
		mode :	1)������ => 1.��ǳ 2.��ǳ 3.��ǳ 4.�ڿ�ǳ
					2)��Ź�� => 1.�⺻ 2.��� 3.��� �� Ż��
					3)����û���� => 1.���� 2.���
		temper :	1)������
						2)����
*/
typedef struct Status {//���� ����¿��� �ʿ䰡 ����
	char deviceName[MAX_NAME];
	int status;		// �ʱ�ȭ �� -1
	int mode;		// �ʱ�ȭ �� 0
	int temper;	// �ʱ�ȭ �� 23
}Status;

/*		���� ���� ����ü
		deviceName : ��ġ��
		hour : ��
		min : ��
		reStatus : ON - 1, OFF - 0
		mode :	1)������ => 1.��ǳ 2.��ǳ 3.��ǳ 4.�ڿ�ǳ
					2)��Ź�� => 1.�⺻ 2.��� 3.��� �� Ż��
					3)����û���� => 1.���� 2.���
*/
typedef struct Reserve {
	char deviceName[MAX_NAME];
	int hour;		// �ʱ�ȭ �� : -1
	int min;			// �ʱ�ȭ �� : -1
	int reStatus;	// �ʱ�ȭ �� : -1
	int mode;		// �ʱ�ȭ �� : 0
}Reserve;

/*		��ġ ����ü
		deviceName : ��ġ��
		company : ���� ȸ��
		conductName : ǰ��
		reserCnt : ���� Ƚ��
		indate : �������
*/
typedef struct Device {
	char deviceName[MAX_NAME];
	char company[MAX_NAME];
	char indate[10];
	int reserCnt;
}Device;

typedef struct Node {
	struct Node *prev, *next;
}Node;

typedef struct List {
	Node *head, *tail;
}List;

/*
===========<Device.txt>============
��� �Ǿ� �ִ� ��ġ���� ��� ������ ����.

===========<Status.txt>============
��ġ���� ���� ����

=========<Reserve.txt>===========
���� ������ �Ǿ��ִ� ��ġ���� ������ ����.

=========<Company.txt>===========
���� ������ ���� ȸ�� �� ��ǰ ��ȣ ���� ����.

=========<Environ.txt>=========
ȯ�� ������ ����	(���������� �̺�Ʈ ����)
�ó����� ����


*/