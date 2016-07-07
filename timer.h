#ifndef __CDZTIMER_H__
#define __CDZTIMER_H__

#include <sys/time.h>
#include "event2/event_struct.h"

enum time_number_t {
	CDZ_TIMER_0 = 0,
	CDZ_TIMER_1,
	CDZ_TIMER_2,
	CDZ_TIMER_3,
	CDZ_IIMER_MAX
};
enum time_state_t {
	TIMER_STATE_ON,
	TIMER_STATE_OFF
};
struct cdz_timer_struct {
	int state;
	struct timeval tv;
	struct event tevent;
	void (*function)(evutil_socket_t, short, void *);
};
struct cdz_timer {
	struct event_base *time_base;
	struct cdz_timer_struct timers[CDZ_IIMER_MAX]; 
};

int cdz_timer_init(struct event_base *ebase);

int cdz_timer_on(int index);

void cdz_timer_off(int index);

#endif
