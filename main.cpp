#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include "mainlevel.h"

int main(void) {

	//	ȫ�ֱ���
	BODY* s_head = NULL;
	FOOD* f_head = NULL;
	int accumulate = 0;

	//	����
	startup(&s_head, &f_head);
	while (1) {
		show(s_head, f_head);
		updateWithoutInput(&s_head, &f_head, &accumulate);
		updateWithInput(s_head);
		
		FlushBatchDraw();
		//cleardevice();
		Sleep(10);
	}

	return 0;
}