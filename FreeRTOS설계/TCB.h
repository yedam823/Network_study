#include<stdio.h>
#include<windows.h>

typedef enum {
	READY, //실행준비
	RUNNING, //실행중
	WAITING, //기다리는중
	TERMINATED //종료됨
}TaskState;

typedef struct {
	int id;
	char name[20];
	int priority;
	TaskState state;

	HANDLE thread_handle;
	DWORD thread_id;
}TCB;

#define MAX_TASKS 10
TCB task_table[MAX_TASKS];
int task_count;



typedef void (*Task_Function)(void*);

int Task_Create(Task_Function func, const char* name, int priority);

