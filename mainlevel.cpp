#include <graphics.h>
#include <conio.h>
#include "mainlevel.h"

#define GAME_WIDE 960
#define GAME_HIGH 550

#define START_SNAKE_LONG 10
#define START_SNAKE_X (GAME_WIDE/2)
#define START_SNAKE_Y (GAME_HIGH/2)
#define START_SNAKE_R 10

#define GAME_FOOD_NUM 25

FOOD* generatefood(FOOD* const head);
BODY* generatebody(BODY* head);

void startup(BODY** s_head, FOOD** f_head) {
	closegraph();
	initgraph(GAME_WIDE, GAME_HIGH);

	//	初始化小虵
	for (int i = 0; i < START_SNAKE_LONG; i++)
	{
		BODY* p = (BODY*)malloc(sizeof(BODY));

		//	初始化虵
		if (p == *s_head) {
			p->color = GREEN;
		}
		else {
			p->color = BLUE;
		}
		p->x = START_SNAKE_X;
		p->y = START_SNAKE_Y - i * START_SNAKE_R * 2;
		p->r = START_SNAKE_R;
		p->next = NULL;

		BODY* last = *s_head;
		if (last) {
			while (last->next) {
				last = last->next;
			}
			last->next = p;
		}
		else {
			*s_head = p;
		}
	}

	//	初始化食物点
	for (int i = 0; i < GAME_FOOD_NUM; i++)
	{
		FOOD* p = (FOOD*)malloc(sizeof(FOOD));

		//	初始化
		p->color = RED;
		p->x = rand() % GAME_WIDE;
		p->y = rand() % GAME_HIGH;
		p->r = 2;
		p->state = canEat;
		p->next = NULL;

		FOOD* last = *f_head;
		if (last) {
			while (last->next) {
				last = last->next;
			}
			last->next = p;
		}
		else {
			*f_head = p;
		}
	}

}

void show(BODY* s_head, FOOD* f_head) {

	IMAGE background;
	loadimage(&background, _T(".\\pic\\bg.jpg"));
	putimage(0, 0, &background);
	setbkmode(TRANSPARENT);

	//	画所有的虵身子
	for (BODY* i = s_head; i; i = i->next)
	{
		setcolor(BLACK);
		setfillcolor(i->color);
		fillcircle(i->x, i->y, i->r);
	}

	//	画所有的食物点
	for (FOOD* i = f_head; i; i = i->next)
	{
		if (i->state == canEat) {
			setcolor(BLACK);
			setfillcolor(i->color);
			fillcircle(i->x, i->y, i->r);
		}
	}
}

void updateWithoutInput(BODY** s_head, FOOD** f_head, int* accumulate, char* currentV) {

	//	虵所有关节的移动
	for (BODY* i = *s_head; i->next; i = i->next)
	{
		if ((i->x - i->next->x) * (i->x - i->next->x) + (i->y - i->next->y) * (i->y - i->next->y) > (i->r + i->next->r) * (i->r + i->next->r) + 1) {
			if (i->x > i->next->x) {
				i->next->x = i->next->x + 3;
			}
			else if (i->x < i->next->x) {
				i->next->x = i->next->x - 3;
			}
			//
			if (i->y > i->next->y) {
				i->next->y = i->next->y + 3;
			}
			else if (i->y < i->next->y) {
				i->next->y = i->next->y - 3;
			}
		}
	}

	//	吃食物
	for (BODY* i = *s_head; i; i = i->next)
	{
		for (FOOD* j = *f_head; j; j = j->next)
		{
			if (j->state == canEat) {
				if (
					(j->x >= i->x - i->r) &&
					(j->x <= i->x + i->r) &&
					(j->y >= i->y - i->r) &&
					(j->y <= i->y + i->r)) {
					(*accumulate)++;
					*f_head = generatefood(*f_head);
					j->state = notCanEat;
				}
			}
		}
	}

	//	当积累达到3时长度加一
	if (*accumulate >= 3) {
		*accumulate -= 3;
		(*s_head) = generatebody(*s_head);
	}

	//	撞墙死亡
	for (BODY* i = (*s_head)->next->next; i; i = i->next)
	{
		if (
			(i->x - (*s_head)->x) * (i->x - (*s_head)->x) + (i->y - (*s_head)->y) * (i->y - (*s_head)->y) < (i->r + (*s_head)->r) * (i->r + (*s_head)->r)
			) {
			exit(1);
		}
	}

	//	碰自己死亡
	for (BODY* i = *s_head; i; i = i->next)
	{
		if (
			i->x - i->r <= 0 ||
			i->x + i->r >= GAME_WIDE ||
			i->y - i->r <= 0 ||
			i->y + i->r >= GAME_HIGH
			) {
			exit(0);
		}
	}
	
	//	移动
	switch (*currentV)
	{
	case 'a':
		((*s_head)->x) = ((*s_head)->x) - 3;
		break;
	case 'd':
		((*s_head)->x) = ((*s_head)->x) + 3;
		break;
	case 'w':
		((*s_head)->y) = ((*s_head)->y) - 3;
		break;
	case 's':
		((*s_head)->y) = ((*s_head)->y) + 3;
		break;
	default:
		break;
	}
}

void updateWithInput(BODY* s_head, char* currentV) {
	
	//	控制方向
	char chInput = '0';
	if (_kbhit())
	{
		chInput = _getch();
	}

	//	判定键盘输入是有效的
	if (chInput == 'a' || chInput == 's' || chInput == 'd' || chInput == 'w') {
		*currentV = chInput;
	}
}

//	生成一个点
FOOD* generatefood(FOOD* head) {
	//	找到结尾
	FOOD* last = head;
	while (last->next)
		last = last->next;

	//	制造节点
	FOOD* p = (FOOD*)malloc(sizeof(FOOD));
	last->next = p;
	p->color = RED;
	p->x = rand() % GAME_WIDE;
	p->y = rand() % GAME_HIGH;
	p->r = 2;
	p->state = canEat;
	p->next = NULL;

	return head;
}

//	生成一个虵节点
BODY* generatebody(BODY* head) {
	//	找到结尾
	BODY* last = head;
	while (last->next)
		last = last->next;

	//	制造节点
	BODY* p = (BODY*)malloc(sizeof(BODY));
	last->next = p;
	p->color = BLUE;
	p->x = last->x;
	p->y = last->y;
	p->r = START_SNAKE_R;
	p->next = NULL;

	return head;
}