#include "net.h"
#define ASDU_I_FRAME 0x00
struct send_list station_send_list ;

void frame_get_number(unsigned char *frame, int len, int *v_s, int *v_r)
{
	/*获取已发送数据帧手法序列号*/
	*v_s = 0x00;
	*v_r = 0x01;
}

struct send_buffer_node *sbuffer_new(unsigned char *asdu, int len)
{
	struct send_buffer_node *np = NULL; 
	if(len > 65535 || len < 0){
		return NULL;
	}
	if(asdu == NULL)
		return NULL;
	np = (struct send_buffer_node *)malloc(sizeof(*np));
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
void sbuffer_del(struct send_buffer_node *np)
{
	if(np->frame)
		free(np->frame);
	free(np);
}
int frame_i_list_add(unsigned char *asdu, int len)
{
	struct send_buffer_node *np = sbuffer_new(asdu, len);
	if(np == NULL)
		return -ENOMEM;
	/* lock start*/
	list_add(&(np->list), &(station_send_list.list));
	station_send_list.number ++;
	/* lock end*/
	return 0;	
}
int frame_i_list_del(int current_send_number, int current_recv_number)
{
	struct send_buffer_node *np = NULL;
	struct list_head *tmp,*pos;
	int s_number,r_number;
	int delete = 0;
	/* lock start */
	list_for_each_safe(pos, tmp, &(station_send_list.list)){
		np = list_entry(pos, struct send_buffer_node, list);
		frame_get_number(np->frame, np->len, &s_number, &r_number);	
		/*XXX:判断条件需要确认一下*/
		if(s_number < current_send_number){
			list_del(pos);
			delete ++;
			sbuffer_del(np);
		}
	}
	station_send_list.number -= delete; 
	/* lock start */
	return station_send_list.number;
}
int cdz_station_send_init(void)
{
	INIT_LIST_HEAD(&(station_send_list.list));
	station_send_list.number = 0;
	return 0;
}
int cdz_station_send_fini(void)
{
	return 0;
}
int cdz_station_send(unsigned char *asdu, int type, int len)
{
	/* add I_FRAME into list */
	if(type == ASDU_I_FRAME){
		if(frame_i_list_add(asdu, len) != 0){
			fprintf(stderr, "%s():L%d\n",__FUNCTION__,__LINE__);
		}
	}
	return 0;
}
