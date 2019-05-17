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

/* �����߳̿��ƿ� */
rt_thread_t led1_thread = RT_NULL;
rt_thread_t led2_thread = RT_NULL;
rt_thread_t task3_thread = RT_NULL;

int task_init()
{
	led1_thread =                        /* �߳̿��ƿ�ָ�� */
	rt_thread_create(	"led1",              /* �߳����� */
						led1_thread_entry,   /* �߳���ں��� */
						RT_NULL,             /* �߳���ں������� */
						THREAD1_STACK_SIZE,   /* �߳�ջ��С */
						THREAD1_PRIORITY,     /* �̵߳����ȼ� */
						THREAD1_TIMESLICE);   /* �߳�ʱ��Ƭ */

	if(led1_thread != RT_NULL)
	{
		rt_thread_startup(led1_thread);
	}

	led2_thread =
	rt_thread_create(	"led2",              /* �߳����� */
						led2_thread_entry,   /* �߳���ں��� */
						RT_NULL,             /* �߳���ں������� */
						THREAD2_STACK_SIZE,   /* �߳�ջ��С */
						THREAD2_PRIORITY,     /* �̵߳����ȼ� */
						THREAD2_TIMESLICE);   /* �߳�ʱ��Ƭ */

	if(led2_thread != RT_NULL)
	{
		rt_thread_startup(led2_thread);
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
	return true;
}


/* ���������RT_SAMPLES_AUTORUN������뵽��ʼ���߳����Զ����� */
#if defined (RT_SAMPLES_AUTORUN) && defined(RT_USING_COMPONENTS_INIT)
	INIT_APP_EXPORT(task_init);
#endif
/* ������ msh �����б��� */
//MSH_CMD_EXPORT(task_init, run signal sample);


