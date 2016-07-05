#include "net.h"
#define ASDU_I_FRAME 0x00
struct send_list station_send_list;

void frame_get_number(unsigned char *frame, int len, int *v_s, int *v_r)
{
	/*获取已发送数据帧手法序列号*/
	*v_s = 0x00;
	*v_r = 0x01;
}

struct send_buffer_node *sbuffer_new(unsigned char *asdu, int len)
{
	struct send_buffer_node *np = malloc(sizeof(struct send_buffer_node));
	if(len > 65535 || len < 0){
		return NULL;
	}
	if(np == NULL){
		fprintf(stderr, "%s():L%d\n",__FUNCTION__,__LINE__);
		goto out;
	}
	memset(np, 0x00, sizeof(*np));
	np->frame = (char *)malloc(len);
	if(np->frame == NULL){
		fprintf(stderr, "%s():L%d\n",__FUNCTION__,__LINE__);
		goto out;
	}
	memcpy(np->frame, asdu, len);	
	return np;
out:
	if(np)
		free(np);
	return NULL;
}
int frame_i_list_add(unsigned char *asdu, int len)
{
	struct send_buffer_node *np = sbuffer_new(asdu, len);
	if(np == NULL){
		return -ENOMEM;
	}
	list_add(&(station_send_list.list), &(np->list));
	return 0;	
}
int frame_i_list_del(int current_send_number, int current_recv_number)
{
	list_for_each_safe(_){
	}
}
int cdz_station_send(unsigned char *asdu, int type, int len)
{
	/*
	add I_FRAME into list
	*/
	if(type == ASDU_I_FRAME){
		if(frame_i_list_add(asdu, len) != 0){
			fprintf(stderr, "%s():L%d\n",__FUNCTION__,__LINE__);
		}
	}
	return 0;
}
