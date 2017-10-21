#include "thing.h"

int main(void)
{
    DATA_TYPE2 data_buff2[DATA_NUM2];
    int i;
    
    int udp_sock;
    fd_set fds;
    struct timeval time_val;
    struct sockaddr_in saddr_in;
    struct in_addr in_a;

    for(i = 0; i < DATA_NUM2; i++) data_buff2[i] = i + 1;
    
    saddr_in.sin_family=AF_INET;
    saddr_in.sin_port=htons(PORT);
    inet_aton(IP_ADDR,&in_a);
    saddr_in.sin_addr=in_a;

    udp_sock=socket(PF_INET,SOCK_DGRAM,0);

    FD_ZERO(&fds);
    FD_SET(udp_sock,&fds);

    time_val.tv_sec=TIV_SEC;
    time_val.tv_usec=0;

    if(select(udp_sock+1,NULL,&fds,NULL,&time_val)>0)
    {
      	i=sendto(udp_sock,data_buff2,sizeof(DATA_TYPE2)*DATA_NUM2,0,
       			(struct sockaddr *)&saddr_in,sizeof(saddr_in));
       	printf("Number of send bytes = %d.\n",i);
    }
    close(udp_sock); 
    return 0;
}
