#include "thing.h"

int main(void)
{
    DATA_TYPE2 data_buf2[DATA_NUM2];
    int i;

    int udp_sock;
    fd_set fds;
    struct timeval time_val;
    struct sockaddr_in saddr_in;

    udp_sock=socket(PF_INET,SOCK_DGRAM,0);

    saddr_in.sin_family=AF_INET;
    saddr_in.sin_addr.s_addr=INADDR_ANY;
    saddr_in.sin_port=htons(PORT);

    bind(udp_sock, (struct sockaddr *) &saddr_in, sizeof(saddr_in));

    while(1)
    {
      FD_ZERO(&fds);
      FD_SET(udp_sock,&fds);

      time_val.tv_usec=0;
      time_val.tv_sec=TIV_SEC;

      if(select(udp_sock+1,&fds,NULL,NULL,&time_val)>0)
      {
     i=recvfrom(udp_sock,data_buf2,sizeof(DATA_TYPE2)*DATA_NUM2,0,NULL,NULL);
       	printf("Number of recived bytes = %d.\n",i);
       	for(i=0;i<DATA_NUM2;i++)
                printf("num - %d -> value - %d\n",i+1,data_buf2[i]);
      }
    }
    close(udp_sock);
    return 0;
}
