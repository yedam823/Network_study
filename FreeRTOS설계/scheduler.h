#pragma once

#define MAX_TASKS 10

#include"TCB.h"
#include<stdint.h>

typedef enum {
	OS_OK = 0,
	OS_ERROR,
	OS_TIMEOUT,
	OS_ERR_PEND_ISR,
	OS_ERR_OWNERSHIP
}OS_STATUS;

typedef struct {
	int lock_count;
	TCB* owner;
	TCB* wait_list[MAX_TASKS]; //우선순위 큐로 구현하기
	int wait_count;
}mutex_t;

TCB* running_task = NULL;

OS_STATUS Mutex_Lock(mutex_t* mutex, uint32_t timeout_ms);
OS_STATUS Mutex_Unlock(mutex_t* mutex);
OS_STATUS semaphore(void* arg);
void Queue(void* arg);