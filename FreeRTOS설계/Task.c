#include "Task.h"
#include <stdio.h>
#include<windows.h>

void task1(void) {
	while (1) {
		printf("task1이 돌아가고 있습니다.");
		Sleep(500);
	}
}

void task2(void) {
	while (1) {
		printf("task2이 돌아가고 있습니다.");
		Sleep(500);
	}
}

void task3(void) {
	while (1) {
		printf("task3이 돌아가고 있습니다.");
		Sleep(500);
	}
}