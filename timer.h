#ifndef __CDZTIMER_H__
#define __CDZTIMER_H__

#include <sys/time.h>
#include "event2/event_struct.h"

enum time_state_t {
	TIMER_STATE_ON,
	TIMER_STATE_OFF
};
struct cdz_timer {
	char *name;
	struct event tevent;
	struct timeval tv;
	int state;
};

int cdz_timer_init(struct event_base *ebase);
#endif
