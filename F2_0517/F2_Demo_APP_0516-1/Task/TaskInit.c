/******************************************************************************
File name  : TaskInit.c
Description: ��Ҫʵ�������ʼ��
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

/* �����߳̿��ƿ� */
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
* @Description	:��ʼ��������
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
					&msg_pool[0],/* �ڴ��ָ��msg_pool */
					256 - sizeof(void*),/* ÿ����Ϣ�Ĵ�С�� 128 - void* */
					sizeof(msg_pool), /* �ڴ�صĴ�С��msg_pool�Ĵ�С */
					RT_IPC_FLAG_FIFO);/* ����ж���̵߳ȴ������������ȵõ��ķ���������Ϣ */

	if(mq_result != RT_EOK)
	{
		rt_kprintf("init message queue failed.\n");  
		return -1;
	}

	message_handler =  //��Ϣ�ж�
	rt_timer_create(	"message irq",
						message_handler_entry,
						RT_NULL,
						10,
						RT_TIMER_FLAG_PERIODIC);

	if(message_handler != RT_NULL)
	{
		rt_timer_start(message_handler);
	}

	tim1_thread =  //�����Զ�ʱ��
	rt_timer_create(	"tim1",
						tim1_thread_entry,
						RT_NULL,
						50,
						RT_TIMER_FLAG_PERIODIC);

	if(tim1_thread != RT_NULL)
	{
		rt_timer_start(tim1_thread);
	}

	tim2_thread = //���ζ�ʱ��
	rt_timer_create(	"tim2",
						tim2_thread_entry,
						RT_NULL,
						100,
						RT_TIMER_FLAG_ONE_SHOT);

	if(tim2_thread != RT_NULL)
	{
		rt_timer_start(tim2_thread);
	}

	task1_thread =                        /* �߳̿��ƿ�ָ�� */
	rt_thread_create(	"task1",              /* �߳����� */
						task1_thread_entry,   /* �߳���ں��� */
						RT_NULL,             /* �߳���ں������� */
						THREAD1_STACK_SIZE,   /* �߳�ջ��С */
						THREAD1_PRIORITY,     /* �̵߳����ȼ� */
						THREAD1_TIMESLICE);   /* �߳�ʱ��Ƭ */

	if(task1_thread != RT_NULL)
	{
		rt_thread_startup(task1_thread);
	}

	task2_thread =
	rt_thread_create(	"task2",              /* �߳����� */
						task2_thread_entry,   /* �߳���ں��� */
						RT_NULL,             /* �߳���ں������� */
						THREAD2_STACK_SIZE,   /* �߳�ջ��С */
						THREAD2_PRIORITY,     /* �̵߳����ȼ� */
						THREAD2_TIMESLICE);   /* �߳�ʱ��Ƭ */

	if(task2_thread != RT_NULL)
	{
		rt_thread_startup(task2_thread);
	}

	task3_thread =
	rt_thread_create(	"task3",              /* �߳����� */
						task3_thread_entry,   /* �߳���ں��� */
						RT_NULL,             /* �߳���ں������� */
						THREAD3_STACK_SIZE,   /* �߳�ջ��С */
						THREAD3_PRIORITY,     /* �̵߳����ȼ� */
						THREAD3_TIMESLICE);   /* �߳�ʱ��Ƭ */

	if(task3_thread != RT_NULL)
	{
		rt_thread_startup(task3_thread);
	}

	task4_thread =
	rt_thread_create(	"task4",              /* �߳����� */
						task4_thread_entry,   /* �߳���ں��� */
						RT_NULL,             /* �߳���ں������� */
						THREAD4_STACK_SIZE,   /* �߳�ջ��С */
						THREAD4_PRIORITY,     /* �̵߳����ȼ� */
						THREAD4_TIMESLICE);   /* �߳�ʱ��Ƭ */

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


