#ifndef __NET_H__
#define __NET_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "list.h"
struct send_buffer_node {
	struct list_head list;
	void *frame;
	int len;
};
struct send_list {
	struct list_head list;
	int number;
};
int cdz_station_send(unsigned char *asdu, int type, int len);
#endif
