#ifndef _runtask1_h
#define _runtask1_h
#include "TaskInit.h"

void task1_thread_entry(void* parameter);
void task2_thread_entry(void* parameter);
void task3_thread_entry(void* parameter);
void message_handler_entry(void* parameter);
void tim1_thread_entry(void* parameter);
void tim2_thread_entry(void* parameter);
#endif

