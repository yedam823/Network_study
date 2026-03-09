#include "TCB.h"
#include <assert.h>

int Task_Create(Task_Function func, const char* name, int priority) {
	if (task_count >= MAX_TASKS) return -1;

	TCB* tcb = &task_table[task_count];
	tcb->id = task_count;
	strcpy_s(tcb->name, sizeof(tcb->name), name);
	tcb->priority = priority;
	tcb->state = READY;

	tcb->thread_handle = CreateThread( // 사용할 스레드를 생성함
		NULL, 0, (LPTHREAD_START_ROUTINE)func, NULL, CREATE_SUSPENDED, &tcb->thread_id
	);
	assert(tcb->thread_handle != NULL);

	return task_count++;
}