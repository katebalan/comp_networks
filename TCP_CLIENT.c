#include "thing.h"

int main(void) {
  DATA_TYPE1 data_buff1[DATA_NUM1];

  int i;
  
  int tcp_sock_bool;
  int tcp_sock_double;
  fd_set fds;
  struct timeval time_val;
  struct sockaddr_in saddr_in;
  struct in_addr in_a;

  for(i = 0; i < DATA_NUM1; i++) data_buff1[i] = false;

  saddr_in.sin_family = AF_INET;
  saddr_in.sin_port = htons(PORT);
  inet_aton(IP_ADDR, &in_a);
  saddr_in.sin_addr = in_a;

  // PF_INET --> IPv4 протоколы Интернет
  // SOCK_STREM -->  
  // Обеспечивает создание двусторонних  надежных  и последовательных потоков байтов, 
  // поддерживающих соединения. 
  // Может также поддерживаться механизм внепоточных данных.
  tcp_sock_bool = socket(PF_INET, SOCK_STREAM, 0);

  if(connect(tcp_sock_bool, (struct sockaddr *)&saddr_in, sizeof(saddr_in)) != -1) {
    FD_ZERO(&fds);
    FD_SET(tcp_sock_bool, &fds);

    time_val.tv_sec = TIV_SEC;
    time_val.tv_usec = 0;

    if(select(tcp_sock_bool + 1, NULL, &fds, NULL, &time_val) > 0) {
		  i = write(tcp_sock_bool, data_buff1, sizeof(DATA_TYPE1) * DATA_NUM1);
   		printf("Number of send bytes = %d\n", i);
   	}
  }
  else perror("Connection to server failed");

  shutdown(tcp_sock_bool, 2);
  close(tcp_sock_bool);
  return 0;
}
