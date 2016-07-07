#include <sys/socket.h>
#include <sys/types.h>
#include "net.h"

struct cdz_socket_struct cdz; 

int cdz_socket_create(struct cdz_cfg_struct *ccs)
{
	int socketfd = 0,ret = 0;
	struct sockaddr_in server;
	memset(&server, 0x00, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(ccs->station_port);
	inet_aton(ccs->station_address, &server.sin_addr);
	socketfd = socket(PF_INET, SOCK_STREAM, 0);
	if(socketfd < 0){
		fprintf(stderr, "E:%s()-L%d:%s\n",__FUNCTION__,__LINE__,strerror(errno));
		return socketfd;
	}
	ret = connect(socketfd, (struct sockaddr*)&server, sizeof(struct sockaddr));
	if(ret < 0){
		fprintf(stderr, "E:%s()-L%d:%s\n",__FUNCTION__,__LINE__,strerror(errno));
		goto out;
	}
	return socketfd;
out:
	close(socketfd);	
	return ret;	
}
/*这个函数将会在*/
void cdz_socket_read_callback(struct bufferevent *bev, void *ctx)
{
	
}
