#include "util.h"
#include "timer.h"
#include "event2/event.h"

#define TIMER_SENDWORK_TIMEOUT 1
#define TIMER_T0_TIMEOUT 2 
#define TIMER_T1_TIMEOUT 15
#define TIMER_T2_TIMEOUT 10 
#define TIMER_T3_TIMEOUT 20

static struct cdz_timer sendwork,t0,t1,t2,t3;

void sendwork_timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	struct cdz_timer *cp = arg;
	struct timeval newtime;
	evutil_gettimeofday(&newtime, NULL);
	fprintf(stderr, "D:%s()-L%d:%d\n",__FUNCTION__,__LINE__,(int)newtime.tv_sec);
	sleep(20);
	evtimer_add(&cp->tevent, &cp->tv);
}
void t0_timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	struct cdz_timer *cp = arg;
	struct timeval newtime;
	evutil_gettimeofday(&newtime, NULL);
	fprintf(stderr, "D:%s()-L%d:%d\n",__FUNCTION__,__LINE__,(int)newtime.tv_sec);
	evtimer_add(&cp->tevent, &cp->tv);
}
void t1_timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	struct cdz_timer *cp = arg;
	struct timeval newtime;
	evutil_gettimeofday(&newtime, NULL);
	fprintf(stderr, "D:%s()-L%d:%d\n",__FUNCTION__,__LINE__,(int)newtime.tv_sec);
	evtimer_add(&cp->tevent, &cp->tv);
}
void t2_timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	struct cdz_timer *cp = arg;
	struct timeval newtime;
	evutil_gettimeofday(&newtime, NULL);
	fprintf(stderr, "D:%s()-L%d:%d\n",__FUNCTION__,__LINE__,(int)newtime.tv_sec);
	evtimer_add(&cp->tevent, &cp->tv);
}
void t3_timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	struct cdz_timer *cp = arg;
	struct timeval newtime;
	evutil_gettimeofday(&newtime, NULL);
	fprintf(stderr, "D:%s()-L%d:%d\n",__FUNCTION__,__LINE__,(int)newtime.tv_sec);
	evtimer_add(&cp->tevent, &cp->tv);
}
int cdz_timer_init(struct event_base *ebase)
{
	memset(&sendwork, 0x00, sizeof(sendwork));
	sendwork.name = "";
	sendwork.tv.tv_sec = TIMER_SENDWORK_TIMEOUT;
	evtimer_assign(&sendwork.tevent, ebase, sendwork_timeout_cb, (void*) &sendwork);
	evtimer_add(&sendwork.tevent, &sendwork.tv);

	memset(&t0, 0x00, sizeof(t0));
	t0.name = "";
	t0.tv.tv_sec = TIMER_T0_TIMEOUT;
	evtimer_assign(&t0.tevent, ebase, t0_timeout_cb, (void*) &t0);
	evtimer_add(&t0.tevent, &t0.tv);

	memset(&t1, 0x00, sizeof(t0));
	t1.name = "";
	t1.tv.tv_sec = TIMER_T1_TIMEOUT;
	evtimer_assign(&t1.tevent, ebase, t1_timeout_cb, (void*) &t1);
	evtimer_add(&t1.tevent, &t1.tv);

	memset(&t2, 0x00, sizeof(t2));
	t2.name = "";
	t2.tv.tv_sec = TIMER_T2_TIMEOUT;
	evtimer_assign(&t2.tevent, ebase, t2_timeout_cb, (void*) &t2);
	evtimer_add(&t2.tevent, &t2.tv);

	memset(&t3, 0x00, sizeof(t3));
	t3.name = "";
	t3.tv.tv_sec = TIMER_T3_TIMEOUT;
	evtimer_assign(&t3.tevent, ebase, t3_timeout_cb, (void*) &t3);
	evtimer_add(&t3.tevent, &t3.tv);
	return 0;	
}

struct cdz_timout {
	struct event_base *base;
	struct event 
};
