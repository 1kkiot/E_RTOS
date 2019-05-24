/******************************************************************************
File name  : TaskInit.c
Description: 主要实现任务初始化
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-15
Modify	   : 
Modify Time: 
*******************************************************************************/
#include "TaskInit.h"
#include "RunTask1.h"
#define THREAD1_STACK_SIZE			512
#define THREAD1_PRIORITY			4
#define THREAD1_TIMESLICE			300

#define THREAD2_STACK_SIZE			1024
#define THREAD2_PRIORITY			3
#define THREAD2_TIMESLICE			200

#define THREAD3_STACK_SIZE			1024
#define THREAD3_PRIORITY			5
#define THREAD3_TIMESLICE			500

#define THREAD4_STACK_SIZE			1024
#define THREAD4_PRIORITY			6
#define THREAD4_TIMESLICE			500

/* 定义线程控制块 */
struct rt_messagequeue mq_task;
static rt_uint8_t msg_pool[2048];
rt_err_t mq_result;

rt_timer_t tim1_thread = RT_NULL;
rt_timer_t tim2_thread = RT_NULL;
rt_timer_t message_handler = RT_NULL;

rt_thread_t task1_thread = RT_NULL;
rt_thread_t task2_thread = RT_NULL;
rt_thread_t task3_thread = RT_NULL;
rt_thread_t task4_thread = RT_NULL;

/*******************************************************************************
* @Function		:int task_init()
* @Description	:初始化任务功能
* @Input		:null
* @Output		:null
* @Return		:true
* @Others		:null
*******************************************************************************/
int task_init()
{

	mq_result =
	rt_mq_init(		&mq_task,
					"mqt",
					&msg_pool[0],/* 内存池指向msg_pool */
					256 - sizeof(void*),/* 每个消息的大小是 128 - void* */
					sizeof(msg_pool), /* 内存池的大小是msg_pool的大小 */
					RT_IPC_FLAG_FIFO);/* 如果有多个线程等待，按照先来先得到的方法分配消息 */

	if(mq_result != RT_EOK)
	{
		rt_kprintf("init message queue failed.\n");  
		return -1;
	}

	message_handler =  //消息中断
	rt_timer_create(	"message irq",
						message_handler_entry,
						RT_NULL,
						10,
						RT_TIMER_FLAG_PERIODIC);

	if(message_handler != RT_NULL)
	{
		rt_timer_start(message_handler);
	}

	tim1_thread =  //周期性定时器
	rt_timer_create(	"tim1",
						tim1_thread_entry,
						RT_NULL,
						50,
						RT_TIMER_FLAG_PERIODIC);

	if(tim1_thread != RT_NULL)
	{
		rt_timer_start(tim1_thread);
	}

	tim2_thread = //单次定时器
	rt_timer_create(	"tim2",
						tim2_thread_entry,
						RT_NULL,
						100,
						RT_TIMER_FLAG_ONE_SHOT);

	if(tim2_thread != RT_NULL)
	{
		rt_timer_start(tim2_thread);
	}

	task1_thread =                        /* 线程控制块指针 */
	rt_thread_create(	"task1",              /* 线程名字 */
						task1_thread_entry,   /* 线程入口函数 */
						RT_NULL,             /* 线程入口函数参数 */
						THREAD1_STACK_SIZE,   /* 线程栈大小 */
						THREAD1_PRIORITY,     /* 线程的优先级 */
						THREAD1_TIMESLICE);   /* 线程时间片 */

	if(task1_thread != RT_NULL)
	{
		rt_thread_startup(task1_thread);
	}

	task2_thread =
	rt_thread_create(	"task2",              /* 线程名字 */
						task2_thread_entry,   /* 线程入口函数 */
						RT_NULL,             /* 线程入口函数参数 */
						THREAD2_STACK_SIZE,   /* 线程栈大小 */
						THREAD2_PRIORITY,     /* 线程的优先级 */
						THREAD2_TIMESLICE);   /* 线程时间片 */

	if(task2_thread != RT_NULL)
	{
		rt_thread_startup(task2_thread);
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

	task4_thread =
	rt_thread_create(	"task4",              /* 线程名字 */
						task4_thread_entry,   /* 线程入口函数 */
						RT_NULL,             /* 线程入口函数参数 */
						THREAD4_STACK_SIZE,   /* 线程栈大小 */
						THREAD4_PRIORITY,     /* 线程的优先级 */
						THREAD4_TIMESLICE);   /* 线程时间片 */

	if(task4_thread != RT_NULL)
	{
		rt_thread_startup(task4_thread);
	}
	return true;
}



#if defined (RT_SAMPLES_AUTORUN) && defined(RT_USING_COMPONENTS_INIT)
INIT_APP_EXPORT(task_init);
#endif

//MSH_CMD_EXPORT(task_init, run signal sample);


