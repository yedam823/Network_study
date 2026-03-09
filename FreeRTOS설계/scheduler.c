#include "scheduler.h"
#include<stdio.h>

OS_STATUS Mutex_Lock(mutex_t* mutex /*uint32_t timeout_ms*/) { // 추후에 타임아웃 구현하기
	if (mutex == NULL || running_task == NULL) {
		return OS_ERROR;
	}

	if (mutex->owner == running_task) {
		mutex->lock_count++; //재귀 고려
		return OS_OK;
	}

	if (mutex->lock_count == 0) {
		printf("공유자원을 획득했습니다. 뮤텍스 작업을 시작합니다.");
		mutex->owner = running_task;
		mutex->lock_count++;
		return OS_OK;
	}
	else if (mutex->lock_count > 0) {
		if (mutex->owner->priority < running_task->priority) {
			mutex->owner->priority = running_task->priority;
		}
	}

	printf("공유자원을 획득하지 못했습니다. 잠시 대기상태로 전환됩니다.");
	running_task->state = WAITING;
	if (mutex->wait_count < MAX_TASKS) {
		mutex->wait_list[mutex->wait_count++] = running_task;
	}
	SuspendThread(running_task->thread_handle);

	return OS_OK;
}

OS_STATUS Mutex_Unlock(mutex_t* mutex) {
	if (mutex->owner == running_task) {
		mutex->lock_count--;
		if (mutex->lock_count > 0) { return OS_OK; }
		mutex->owner = NULL;
		
		TCB* target_task = NULL;
		if (mutex->wait_count > 0) {
			target_task = mutex->wait_list[0];
			int highest = 0;
			for (int i = 1; i < mutex->wait_count; i++) {
				if (mutex->wait_list[i]->priority > mutex->wait_list[highest]->priority) {
					highest = i;
				}
			}
			target_task = mutex->wait_list[highest];
			mutex->wait_count--;

			target_task->state = READY;
			ResumeThread(target_task->thread_handle);
		}

		return OS_OK;
	}
	return OS_ERROR;
}