#pragma once
#define MAX_NAME 20
#define MAX_COND 30

/*		환경 상태 구조체
		nowTemper : 온도
		clean : 공기 청정도
*/
typedef struct Environ {
	int nowTemper;
	int clean;
}Environ;

/*		장치 상태 구조체
		deviceName : 장치명
		status : ON - 1, OFF - 0
		mode :	1)에어컨 => 1.강풍 2.약풍 3.미풍 4.자연풍
					2)세탁기 => 1.기본 2.쾌속 3.헹굼 및 탈수
					3)공기청정기 => 1.저속 2.고속
		temper :	1)에어컨
						2)수온
*/
typedef struct Status {//파일 입출력에서 필요가 없음
	char deviceName[MAX_NAME];
	int status;		// 초기화 값 -1
	int mode;		// 초기화 값 0
	int temper;	// 초기화 값 23
}Status;

/*		예약 상태 구조체
		deviceName : 장치명
		hour : 시
		min : 분
		reStatus : ON - 1, OFF - 0
		mode :	1)에어컨 => 1.강풍 2.약풍 3.미풍 4.자연풍
					2)세탁기 => 1.기본 2.쾌속 3.헹굼 및 탈수
					3)공기청정기 => 1.저속 2.고속
*/
typedef struct Reserve {
	char deviceName[MAX_NAME];
	int hour;		// 초기화 값 : -1
	int min;			// 초기화 값 : -1
	int reStatus;	// 초기화 값 : -1
	int mode;		// 초기화 값 : 0
}Reserve;

/*		장치 구조체
		deviceName : 장치명
		company : 제조 회사
		conductName : 품번
		reserCnt : 예약 횟수
		indate : 등록일자
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
등록 되어 있는 장치들의 모든 정보를 저장.

===========<Status.txt>============
장치들의 현재 상태

=========<Reserve.txt>===========
예약 설정이 되어있는 장치들의 정보를 저장.

=========<Company.txt>===========
지원 가능한 제조 회사 및 제품 번호 정보 저장.

=========<Environ.txt>=========
환경 정보를 저장	(임의적으로 이벤트 저장)
시나리오 포함


*/