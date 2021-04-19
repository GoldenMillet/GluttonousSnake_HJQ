#pragma once

#include <graphics.h>
#include <conio.h>

//	虵身子的结构体
typedef struct _body {
	int x;
	int y;
	int r;
	COLORREF color;

	struct _body* next;
} BODY ;

//	食物点的结构体
enum a_state {notCanEat, canEat};
typedef struct _food {
	int x;
	int y;
	int r;
	enum a_state state;
	COLORREF color;

	struct _food* next;
} FOOD ;

//	游戏函数
void startup(BODY** s_head, FOOD** f_head);
void show(unsigned int* time, BODY* s_head, FOOD* f_head);
void updateWithoutInput(unsigned int* time, BODY** s_head, FOOD** f_head, int* accumulate, char* currentV);
void updateWithInput(BODY* s_head, char* currentV);