#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>

#define PORT 		2048
#define IP_ADDR 	"127.0.0.1"

#define DATA_NUM1 	10
#define DATA_TYPE1 	bool

#define DATA_NUM2 	10
#define DATA_TYPE2 	double

#define TIV_SEC 	5
