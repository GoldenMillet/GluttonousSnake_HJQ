#pragma once

#include <graphics.h>
#include <conio.h>

//	�F���ӵĽṹ��
typedef struct _body {
	int x;
	int y;
	int r;
	COLORREF color;

	struct _body* next;
} BODY ;

//	ʳ���Ľṹ��
enum a_state {notCanEat, canEat};
typedef struct _food {
	int x;
	int y;
	int r;
	enum a_state state;
	COLORREF color;

	struct _food* next;
} FOOD ;

//	��Ϸ����
void startup(BODY** s_head, FOOD** f_head);
void show(unsigned int* time, BODY* s_head, FOOD* f_head);
void updateWithoutInput(unsigned int* time, BODY** s_head, FOOD** f_head, int* accumulate, char* currentV);
void updateWithInput(BODY* s_head, char* currentV);