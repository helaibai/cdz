#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

#include <event2/event.h>
#include <event2/bufferevent.h>

#include "timer.h"
#include "util.h" 
#include "net.h"

struct cdz_cfg_struct cdz_cfg;

void cdz_bufferevent_read_cb(struct bufferevent *bev, void *ctx)
{
	fprintf(stderr, "D:%s()-L%d\n",__FUNCTION__,__LINE__);
}
void cdz_bufferevent_cb(struct bufferevent *bev, short what, void *ctx)
{
	fprintf(stderr, "D:%s()-L%d\n",__FUNCTION__,__LINE__);
}
#if 1
int main(int argc, char **argv)
{
	int ret;
	memset(&cdz_cfg, 0x00, sizeof(cdz_cfg));
	cdz_log_init();
	ret = cdz_timer_init(NULL);
	if(ret != 0){
		fprintf(stderr, "E:%s()-L%d\n",__FUNCTION__,__LINE__);
		goto out;
	}
	ret = cdz_socket_create(&cdz_cfg);
	if(ret != 0){
		fprintf(stderr, "E:%s()-L%d\n",__FUNCTION__,__LINE__);
		goto out;
	}
	while(1) 
		sleep(3);
out:
	cdz_log_fini();
}
#else
int main(int argc, char **argv)
{

	int ret;
	struct event_base *ebase = NULL;
	struct bufferevent *cdz_bufferevent = NULL;
	struct sockaddr_in server_addr;
	log4c_init();
	log4c_fini();
	ret = cdz_net_loop_init(10, 3);
	if(ret != 0){
		return ret;
	}
	ebase = event_base_new();
	cdz_bufferevent = bufferevent_socket_new(ebase, -1, BEV_OPT_CLOSE_ON_FREE);
	/*Server */
	cdz_socket_init();
	memset(&server_addr, 0, sizeof(server_addr) );
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2404);
	inet_aton("10.0.0.2", &server_addr.sin_addr);

	bufferevent_setcb(cdz_bufferevent, cdz_bufferevent_read_cb, NULL, cdz_bufferevent_cb, NULL);
	ret = bufferevent_socket_connect(cdz_bufferevent, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(ret != 0){
		fprintf(stderr, "E:%s()-L%d:%s\n",__FUNCTION__,__LINE__,strerror(errno));
		goto out;
	}
	ret = bufferevent_enable(cdz_bufferevent, EV_READ|EV_WRITE|EV_PERSIST);
	if(ret != 0){
		fprintf(stderr, "E:%s()-L%d:%s\n",__FUNCTION__,__LINE__,strerror(errno));
		goto out;
	}
	cdz_timer_init(ebase);
	event_base_dispatch(ebase);
out:
	if(ebase)
		event_base_free(ebase);
	if(cdz_bufferevent)
		bufferevent_free(cdz_bufferevent);
	return 0;
}
#endif
