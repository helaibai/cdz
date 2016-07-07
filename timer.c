#include "util.h"
#include "timer.h"
#include "event2/event.h"

struct cdz_timer cdz_timers;


/*参考代码*/
#if 0
void timeout_function(evutil_socket_t fd, short event, void *arg)
{
	struct cdz_timer *cp = arg;
	struct timeval newtime;
	evutil_gettimeofday(&newtime, NULL);
	fprintf(stderr, "D:%s()-L%d:%d\n",__FUNCTION__,__LINE__,(int)newtime.tv_sec);
	evtimer_add(&cp->tevent, &cp->tv);
}
#endif
void timeout_0_function(evutil_socket_t fd, short event, void *arg)
{
}
void timeout_1_function(evutil_socket_t fd, short event, void *arg)
{
}
void timeout_2_function(evutil_socket_t fd, short event, void *arg)
{
}
void timeout_3_function(evutil_socket_t fd, short event, void *arg)
{
}
#define CDZ_TIMER_SETUP(__index, __time,__function) do{		\
	cdz_timers.timers[(__index)].state = TIMER_STATE_OFF;	\
	cdz_timers.timers[(__index)].tv.tv_sec = (__time);	\
	cdz_timers.timers[(__index)].function = (__function);	\
	evtimer_assign(&(cdz_timers.timers[(__index)].tevent), cdz_timers.time_base,(__function), NULL);\
}while(0)
int cdz_timer_on(int index)
{
	return evtimer_add(&(cdz_timers.timers[index].tevent),
		&(cdz_timers.timers[index].tv));
}
void cdz_timer_off(int index)
{
	event_del(&(cdz_timers.timers[index].tevent));
}
void *timer_run(void *arg)
{
	memset(&cdz_timers, 0x00, sizeof(cdz_timers));
	cdz_timers.time_base = event_base_new();
	/*在这里设置，超时处理函数*/
	CDZ_TIMER_SETUP(CDZ_TIMER_0, 10, timeout_0_function);
	CDZ_TIMER_SETUP(CDZ_TIMER_1, 20, timeout_1_function);
	CDZ_TIMER_SETUP(CDZ_TIMER_2, 15, timeout_2_function);
	CDZ_TIMER_SETUP(CDZ_TIMER_3, 20, timeout_3_function);
	event_base_dispatch(cdz_timers.time_base);
	return NULL;
}
int cdz_timer_init(struct event_base *ebase)
{
	int ret = 0;
	pthread_t thread_timer;
	ret = pthread_create(&thread_timer, NULL, timer_run, NULL);
	if(ret != 0){
		fprintf(stderr, "E:%s()-L%d\n",__FUNCTION__,__LINE__);
	}
	return ret;
}
