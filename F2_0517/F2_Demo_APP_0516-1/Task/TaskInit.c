#include "TaskInit.h"
#include "RunTask1.h"
#define THREAD1_STACK_SIZE			256
#define THREAD1_PRIORITY			4
#define THREAD1_TIMESLICE			10

#define THREAD2_STACK_SIZE			256
#define THREAD2_PRIORITY			3
#define THREAD2_TIMESLICE			50

#define THREAD3_STACK_SIZE			512
#define THREAD3_PRIORITY			5
#define THREAD3_TIMESLICE			50

/* 定义线程控制块 */
rt_thread_t led1_thread = RT_NULL;
rt_thread_t led2_thread = RT_NULL;
rt_thread_t task3_thread = RT_NULL;

int task_init()
{
	led1_thread =                        /* 线程控制块指针 */
	rt_thread_create(	"led1",              /* 线程名字 */
						led1_thread_entry,   /* 线程入口函数 */
						RT_NULL,             /* 线程入口函数参数 */
						THREAD1_STACK_SIZE,   /* 线程栈大小 */
						THREAD1_PRIORITY,     /* 线程的优先级 */
						THREAD1_TIMESLICE);   /* 线程时间片 */

	if(led1_thread != RT_NULL)
	{
		rt_thread_startup(led1_thread);
	}

	led2_thread =
	rt_thread_create(	"led2",              /* 线程名字 */
						led2_thread_entry,   /* 线程入口函数 */
						RT_NULL,             /* 线程入口函数参数 */
						THREAD2_STACK_SIZE,   /* 线程栈大小 */
						THREAD2_PRIORITY,     /* 线程的优先级 */
						THREAD2_TIMESLICE);   /* 线程时间片 */

	if(led2_thread != RT_NULL)
	{
		rt_thread_startup(led2_thread);
	}

	task3_thread =
	rt_thread_create(	"task3",              /* 线程名字 */
						task3_thread_entry,   /* 线程入口函数 */
						RT_NULL,             /* 线程入口函数参数 */
						THREAD3_STACK_SIZE,   /* 线程栈大小 */
						THREAD3_PRIORITY,     /* 线程的优先级 */
						THREAD3_TIMESLICE);   /* 线程时间片 */

	if(task3_thread != RT_NULL)
	{
		rt_thread_startup(task3_thread);
	}
	return true;
}


/* 如果设置了RT_SAMPLES_AUTORUN，则加入到初始化线程中自动运行 */
#if defined (RT_SAMPLES_AUTORUN) && defined(RT_USING_COMPONENTS_INIT)
	INIT_APP_EXPORT(task_init);
#endif
/* 导出到 msh 命令列表中 */
//MSH_CMD_EXPORT(task_init, run signal sample);


