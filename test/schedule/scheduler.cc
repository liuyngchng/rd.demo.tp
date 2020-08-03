#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "scheduler.h"

struct schedule_entry *events;
static struct timeval zero;
static sigset_t alarm;

/*
	init_scheduler配合schedule_lock，schedule_unlock使用，用来屏蔽当前进程中特定协议的处理
*/
void init_scheduler (void)/*初始化了两个不同的信号集*/
{
    struct sigaction act;
    act.sa_handler = alarm_handler;/*alarm信号执行体*/
#if defined (LINUX) && (__i386__)
    act.sa_restorer = NULL;
#endif
    act.sa_flags = 0;
    sigemptyset (&act.sa_mask);
    sigaddset (&act.sa_mask, SIGALRM);/*将SIGALRM信号添加到信号集sa_mask中，SIGALRM信号会阻塞*/
    sigaction (SIGALRM, &act, NULL);/*安装登记信号*/
    events = NULL;
    zero.tv_usec = 0;
    zero.tv_sec = 0;
    sigemptyset (&alarm);
    sigaddset (&alarm, SIGALRM);/*将SIGALRM信号添加到信号集alarm中，SIGALRM信号会阻塞*/
}

void alarm_handler (int signal)
{
    /* Check queue for events which should be
       executed right now.  Execute them, then
       see how long we should set the next timer
     */
    struct schedule_entry *p = events;
    struct timeval now;
    struct timeval then;
    struct itimerval itv;
    static int cnt = 0;
    cnt++;
    if (cnt != 1)
    {
        /* Whoa, we got called from within ourselves! */
        //log (LOG_DEBUG, "%s : Whoa... cnt = %d\n", __FUNCTION__, cnt);
        return;
    }
    while (events)
    {
        gettimeofday (&now, NULL);
        p = events;
        if (TVLESSEQ (p->tv, now))
        {
            events = events->next;
            /* This needs to be executed, as it has expired.
               It is expected that p->func will free p->data
               if it is necessary */
            (*p->func) (p->data);
            free (p);
        }
        else
            break;
    }
    /* When we get here, either there are no more events
       in the queue, or the remaining events need to happen
       in the future, so we should schedule another alarm */
    if (events)
    {
        then.tv_sec = events->tv.tv_sec - now.tv_sec;
        then.tv_usec = events->tv.tv_usec - now.tv_usec;
        if (then.tv_usec < 0)
        {
            then.tv_sec -= 1;
            then.tv_usec += 1000000;
        }
        if ((then.tv_sec <= 0) && (then.tv_usec <= 0))
        {
            //log (LOG_WARN, "%s: Whoa...  Scheduling for <=0 time???\n",__FUNCTION__);
        }
        else
        {
            itv.it_interval = zero;
            itv.it_value = then;
            setitimer (ITIMER_REAL, &itv, NULL);/*重新定时，时间到后发送SIGALRM信号*/
        }
    }
    cnt--;
}

void schedule_lock ()/*将alarm添加到当前进程阻塞信号集中，信号来时会被阻塞，暂时捕获不到，移除后会捕获?/
{
    while (sigprocmask (SIG_BLOCK, &alarm, NULL));
};

void schedule_unlock ()/*将alarm从当前进程阻塞信号集中移除*/
{
    /* See if we missed any events */
/*	alarm_handler(0); */
    while (sigprocmask (SIG_UNBLOCK, &alarm, NULL));
    raise (SIGALRM);/*用来向本进程发送信号*/
};

struct schedule_entry *schedule (struct timeval tv, void (*func) (void *),
                                 void *data)
{
    /* Schedule func to be run at relative time tv with data
       as arguments.  If it has already expired, run it 
       immediately.  The queue should be in order of
       increasing time */
    struct schedule_entry *p = events, *q = NULL;  /*时间间隔递增的队列*/
    int need_timer = 0;
    struct timeval diff;
    struct itimerval itv;							/*队列中越靠前，越早发生*/
    diff = tv;
    gettimeofday (&tv, NULL);
    tv.tv_sec += diff.tv_sec;  /*转换为本地系统时间*/
    tv.tv_usec += diff.tv_usec;
    if (tv.tv_usec > 1000000)
    {
        tv.tv_sec++;
        tv.tv_usec -= 1000000;/*进制转换*/
    }
    while (p)				
    {
        if (TVLESS (tv, p->tv)) /*tv < p->tv*/
            break;
        q = p;
        p = p->next;
    };
    if (q)
    {
        q->next =
            (struct schedule_entry *) malloc (sizeof (struct schedule_entry));
        q = q->next;
    }
    else
    {	/*时间比队列中的第一个时间还小*/
        q = (struct schedule_entry *) malloc (sizeof (struct schedule_entry));
        events = q;
        need_timer = -1;
    }
    q->tv = tv;
    q->func = func;
    q->data = data;
    q->next = p;
    if (need_timer)
    {
        itv.it_interval = zero;
        itv.it_value = diff;
        setitimer (ITIMER_REAL, &itv, NULL); /*重新修改定时*/

    }
    return q;

}

inline struct schedule_entry *aschedule (struct timeval tv,/*tv传递的为绝对时间*/
                                         void (*func) (void *), void *data)
{
    /* Schedule func to be run at absolute time tv in the future with data
       as arguments */
    struct timeval now;
    gettimeofday (&now, NULL);
    tv.tv_usec -= now.tv_usec;
    if (tv.tv_usec < 0)
    {
        tv.tv_usec += 1000000;
        tv.tv_sec--;
    }
    tv.tv_sec -= now.tv_sec;
    return schedule (tv, func, data);
}

void deschedule (struct schedule_entry *s)/*取消任务*/
{
    struct schedule_entry *p = events, *q = NULL;
    if (!s)
        return;
    while (p)
    {
        if (p == s)
        {
            if (q)
            {
                q->next = p->next;
            }
            else
            {
                events = events->next;
            }
            free (p);
            break;
        }
        q = p;
        p = p->next;
    }
}

/***********************************************/
void func_test(void *data)
{
	struct timeval tv;	
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	printf("task run\n");
	schedule(tv, func_test, NULL);
}

int main(int argc, char *argv[])
{
	struct timeval tv;
	struct timeval timeout;

	printf("------scheduler-------\n");
	init_scheduler ();
	
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	schedule(tv, func_test, NULL);
	
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	while(1){
		select(0,NULL,NULL,NULL, &timeout);
	}
	return 0;
}
