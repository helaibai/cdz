#ifndef __CDZ_NET_H__
#define __CDZ_NET_H__

#include <event2/event.h>
#include <event2/event_struct.h>
#include "util.h"
#include "list.h"
#include "cfg.h"

struct list_node {
	struct list_head list;
	void *frame;
	int frame_size;
};
struct cdz_list {
	struct list_head list;
	int node_number;
};
struct cdz_socket_struct {
	int socket;
	struct event socket_event;
	struct event_base *socket_base;
	struct bufferevent *evbuffer;
	struct cdz_list send_list;
};

extern struct cdz_socket_struct cdz;

static inline void cdz_list_init(struct cdz_list *l)
{
	INIT_LIST_HEAD(&(l->list));
	l->node_number = 0;
}
static inline void cdz_list_add(struct cdz_list *head, struct list_node *new)
{
	list_add(&(new->list), &(head->list));
	head->node_number ++;
}
static inline void cdz_list_del(struct cdz_list *head, struct list_node *del)
{
	list_del(&(del->list));
	head->node_number --;
}

int cdz_socket_create(struct cdz_cfg_struct *ccs);

int cdz_socket_send(void *frame, int type, int len);

#endif
