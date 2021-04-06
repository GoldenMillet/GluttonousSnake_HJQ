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

	//	��ʼ��С�F
	for (int i = 0; i < START_SNAKE_LONG; i++)
	{
		BODY* p = (BODY*)malloc(sizeof(BODY));

		//	��ʼ���F
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

	//	��ʼ��ʳ���
	for (int i = 0; i < GAME_FOOD_NUM; i++)
	{
		FOOD* p = (FOOD*)malloc(sizeof(FOOD));

		//	��ʼ��
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

	//	�����е��F����
	for (BODY* i = s_head; i; i = i->next)
	{
		setcolor(BLACK);
		setfillcolor(i->color);
		fillcircle(i->x, i->y, i->r);
	}

	//	�����е�ʳ���
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

	//	�F���йؽڵ��ƶ�
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

	//	��ʳ��
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

	//	�����۴ﵽ3ʱ���ȼ�һ
	if (*accumulate >= 3) {
		*accumulate -= 3;
		(*s_head) = generatebody(*s_head);
	}

	//	ײǽ����
	for (BODY* i = (*s_head)->next->next; i; i = i->next)
	{
		if (
			(i->x - (*s_head)->x) * (i->x - (*s_head)->x) + (i->y - (*s_head)->y) * (i->y - (*s_head)->y) < (i->r + (*s_head)->r) * (i->r + (*s_head)->r)
			) {
			exit(1);
		}
	}

	//	���Լ�����
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
	
	//	�ƶ�
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
	
	//	���Ʒ���
	char chInput = '0';
	if (_kbhit())
	{
		chInput = _getch();
	}

	//	�ж�������������Ч��
	if (chInput == 'a' || chInput == 's' || chInput == 'd' || chInput == 'w') {
		*currentV = chInput;
	}
}

//	����һ����
FOOD* generatefood(FOOD* head) {
	//	�ҵ���β
	FOOD* last = head;
	while (last->next)
		last = last->next;

	//	����ڵ�
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

//	����һ���F�ڵ�
BODY* generatebody(BODY* head) {
	//	�ҵ���β
	BODY* last = head;
	while (last->next)
		last = last->next;

	//	����ڵ�
	BODY* p = (BODY*)malloc(sizeof(BODY));
	last->next = p;
	p->color = BLUE;
	p->x = last->x;
	p->y = last->y;
	p->r = START_SNAKE_R;
	p->next = NULL;

	return head;
}