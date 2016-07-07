#include "frame.h"
#include "net.h"

#define ASDU_I_FRAME 0x00


void frame_get_number(unsigned char *frame, int len, int *v_s, int *v_r)
{
	/*获取已发送数据帧手法序列号*/
	*v_s = 0x00;
	*v_r = 0x01;
}

struct list_node *list_node_new(unsigned char *apdu, int len)
{
	struct list_node *np = NULL; 
	if(len > 65535 || len < 0){
		return NULL;
	}
	if(apdu == NULL)
		return NULL;
	np = (struct list_node *)malloc(sizeof(*np));
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
	memcpy(np->frame, apdu, len);	
	np->frame_size = len;
	return np;
out:
	if(np)
		free(np);
	return NULL;
}
void list_node_del(struct list_node *np)
{
	if(np->frame)
		free(np->frame);
	free(np);
}
int frame_i_list_add(unsigned char *apdu, int len)
{
	struct list_node *np = list_node_new(apdu, len);
	if(np == NULL)
		return -ENOMEM;
	/* lock start*/
	cdz_list_add(&(cdz.send_list), np);
	/* lock end*/
	return 0;	
}
int frame_i_list_del(int current_send_number, int current_recv_number)
{
	struct list_node *np = NULL;
	struct list_head *tmp,*pos;
	int s_number,r_number;
	int delete = 0;
	/* lock start */
	list_for_each_safe(pos, tmp, &(cdz.send_list.list)){
		np = list_entry(pos, struct list_node, list);
		frame_get_number(np->frame, np->frame_size, &s_number, &r_number);	
		/*XXX:判断条件需要确认一下*/
		if(s_number < current_send_number){
			delete ++;
			cdz_list_del(&(cdz.send_list), np);
			list_node_del(np);
		}
	}
	/* lock start */
	return delete; 
}
int cdz_frame_init(void)
{
	cdz_list_init(&(cdz.send_list));
	return 0;
}
int cdz_station_send_fini(void)
{
	return 0;
}
int cdz_socket_send(void *apdu, int type, int len)
{
	/* add I_FRAME into list */
	if(type == ASDU_I_FRAME){
		if(frame_i_list_add(apdu, len) != 0){
			fprintf(stderr, "%s():L%d\n",__FUNCTION__,__LINE__);
		}
	}
	return 0;
}
