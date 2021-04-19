#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include "mainlevel.h"

int main(void) {

	//	全局变量
	BODY* s_head = NULL;
	FOOD* f_head = NULL;
	int accumulate = 0;
	char currentV = '0';
	unsigned int time = 0;

	//	函数
	//BeginBatchDraw();
	startup(&s_head, &f_head);
	while (1) {
		show(&time, s_head, f_head);
		updateWithoutInput(&time, &s_head, &f_head, &accumulate, &currentV);
		updateWithInput(s_head, &currentV);
		
		FlushBatchDraw();
		Sleep(10);
	}

	EndBatchDraw();
	return 0;
}