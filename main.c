#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

#include <event2/event.h>
#include <event2/bufferevent.h>

#include "timer.h"
#include "log4c.h" 

int station_socket_init(void)
{
	return 0;
}
int station_net_loop_init(int try_times, int time_cell)
{
	int ret = 0;
	/*1. Initaltion GPRS uart*/
	/*2. GRPS module */
	return ret;
}
struct station_struct {
	struct event_base *ebase;
	struct bufferevent *station_bufferevent;
};
void station_bufferevent_read_cb(struct bufferevent *bev, void *ctx)
{
	fprintf(stderr, "D:%s()-L%d\n",__FUNCTION__,__LINE__);
}
void station_bufferevent_cb(struct bufferevent *bev, short what, void *ctx)
{
	fprintf(stderr, "D:%s()-L%d\n",__FUNCTION__,__LINE__);
}
#if 1
int main(int argc, char **argv)
{
	int ret;
	cdz_log_init();
	ret = cdz_timer_init(NULL);
	if(ret != 0){
	
	}
}
#else
int main(int argc, char **argv)
{

	int ret;
	struct event_base *ebase = NULL;
	struct bufferevent *station_bufferevent = NULL;
	struct sockaddr_in server_addr;
	log4c_init();
	log4c_fini();
	ret = station_net_loop_init(10, 3);
	if(ret != 0){
		return ret;
	}
	ebase = event_base_new();
	station_bufferevent = bufferevent_socket_new(ebase, -1, BEV_OPT_CLOSE_ON_FREE);
	/*Server */
	station_socket_init();
	memset(&server_addr, 0, sizeof(server_addr) );
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2404);
	inet_aton("10.0.0.2", &server_addr.sin_addr);

	bufferevent_setcb(station_bufferevent, station_bufferevent_read_cb, NULL, station_bufferevent_cb, NULL);
	ret = bufferevent_socket_connect(station_bufferevent, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(ret != 0){
		fprintf(stderr, "E:%s()-L%d:%s\n",__FUNCTION__,__LINE__,strerror(errno));
		goto out;
	}
	ret = bufferevent_enable(station_bufferevent, EV_READ|EV_WRITE|EV_PERSIST);
	if(ret != 0){
		fprintf(stderr, "E:%s()-L%d:%s\n",__FUNCTION__,__LINE__,strerror(errno));
		goto out;
	}
	cdz_timer_init(ebase);
	event_base_dispatch(ebase);
out:
	if(ebase)
		event_base_free(ebase);
	if(station_bufferevent)
		bufferevent_free(station_bufferevent);
	return 0;
}
#endif
