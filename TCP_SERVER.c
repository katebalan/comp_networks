#include "thing.h"

int main(void) {
  DATA_TYPE1 data_buf1[DATA_NUM1];

  int i;

  int tcp_sock_bool; // дескриптор сокета
  int tcp_sock_double;
  int curr_sock;
  fd_set fds;
  struct timeval time_val;
  // sockaddr_XX (XX - суффикс, обозначающий домен: "un" - Unix, "in" - Internet и т. д.). 
  struct sockaddr_in saddr_in;

  // PF_INET --> IPv4 протоколы Интернет --> domain
  // SOCK_STREM -->  type
  // Обеспечивает создание двусторонних  надежных  и последовательных потоков байтов, 
  // поддерживающих соединения. 
  // Может также поддерживаться механизм внепоточных данных.
  tcp_sock_bool = socket(PF_INET, SOCK_STREAM, 0);
  

  saddr_in.sin_family = AF_INET;
  saddr_in.sin_addr.s_addr = INADDR_ANY;
  saddr_in.sin_port = htons(PORT); // htons (Host TO Network Short) и htonl (Host TO Network Long)

  // присвоить локальный адрес с помощью bind перед тем, как он сможет участвовать в соединении.
  // 2 parametr - указатель на структуру с адресом,
  // 3 parament - длина структури
  bind(tcp_sock_bool, (struct sockaddr *) &saddr_in, sizeof(saddr_in));
  
  listen(tcp_sock_bool, 1);
  
  printf("TCP_SERVER/incide\n");

  while(1) {
    curr_sock = accept(tcp_sock_bool, NULL, 0);

    FD_ZERO(&fds);
    FD_SET(curr_sock, &fds);

    time_val.tv_sec = TIV_SEC;
    time_val.tv_usec = 0;

    if(select(curr_sock + 1, &fds, NULL, NULL, &time_val) > 0) {
     	i = read(curr_sock, data_buf1, sizeof(DATA_TYPE1) * DATA_NUM1);
     	printf("Number of recived bytes = %d\n", i);
     	for(i = 0; i < DATA_NUM1; i++)
        printf("num - %d -> value - %d\n", i + 1, data_buf1[i]);
    }
    close(curr_sock);
  }
  shutdown(tcp_sock_bool, 2);
  close(tcp_sock_bool);

  return 0;
}

// struct sockaddr_in {
//    short int          sin_family;  // Семейство адресов
//    unsigned short int sin_port;    // Номер порта
//    struct in_addr     sin_addr;    // IP-адрес
//    unsigned char      sin_zero[8]; // "Дополнение" до размера структуры sockaddr
// };

// struct in_addr {
//    unsigned long s_addr;
// };
