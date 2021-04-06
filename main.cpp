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

	//	函数
	startup(&s_head, &f_head);
	while (1) {
		show(s_head, f_head);
		updateWithoutInput(&s_head, &f_head, &accumulate, &currentV);
		updateWithInput(s_head, &currentV);
		
		FlushBatchDraw();
		//cleardevice();
		Sleep(10);
	}

	return 0;
}