#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"

#define PORT 4444  //port number to bindto
#define BUF_SIZE 2000 // size of message to be reieved or sent
#define CLADDR_LEN 100 //size of client address



int mb;
int i=0;


struct clientIp{

	char add[CLADDR_LEN]; 
};

struct clientIp clip[50];

void * acceptConn(void * sockfd)
{
	

}



void * receiveMessage(void * socket) {
 int sockfd, ret;
 
 char buffer[BUF_SIZE]; 
 
 sockfd = (int) socket; //derefrencing sockfd  as address of scoekd is passed to void pointer
 
 //empty the buffer
 memset(buffer, 0, BUF_SIZE);  
 
 //infinte loop
for (;;) 
{
	//recvfrom it takes 6 arguments  and return number of bytes recieved
  ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);  
  
  if (ret < 0) {  
   printf("Error receiving data!\n");    
  } else {
   printf("%s: ",clip[i].add);
   fputs(buffer, stdout);
   //printf("\n");
  }
  int kb=ret/1000; //convert ret(in bytes to kilobytes)
  mb+=kb; //add in total kb
  printf("\nKB Recieved is:%d\n",mb);

 }
}

void main() {
 
 struct sockaddr_in addr, cl_addr;
 
 int sockfd, len, ret, newsockfd;
 
 char buffer[BUF_SIZE];
 
 pid_t childpid;
 
  i=0;
 
 pthread_t rThread;
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
 if (sockfd < 0) {
 
			  printf("Error creating socket!\n");
			 

			  exit(1);
 }
 

 printf("Socket created...\n");
 
 memset(&addr, 0, sizeof(addr));
 
 addr.sin_family = AF_INET;
 
 addr.sin_addr.s_addr = INADDR_ANY;
 
 addr.sin_port = PORT;

 
 
 ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 
 if (ret < 0) {
 
  printf("Error binding!\n");
 
  exit(1);
 }
 printf("Binding done...\n");

 printf("Waiting for a connection...\n");
 
 listen(sockfd, 1000);


 len = sizeof(cl_addr);
 
 newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
 
 if (newsockfd < 0) {
 
  printf("Error accepting connection!\n");
 
  exit(1);
 } 

 inet_ntop(AF_INET, &(cl_addr.sin_addr),clip[i].add, CLADDR_LEN);
 
   

 printf("Connection accepted from %s...\n", clip[0].add); 
 
 memset(buffer, 0, BUF_SIZE);
 
 printf("Enter your messages one by one and press return key!\n");

 //creating a new thread for receiving messages from the client
 
 ret = pthread_create(&rThread, NULL, receiveMessage, (void *) newsockfd);
 
 if (ret) {
  printf("ERROR: Return Code from pthread_create() is %d\n", ret);
 
  exit(1);
 }
printf("\nServerr:");
 while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
 printf("\nServer:");
  ret = sendto(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, len);  
 
  if (ret < 0) {  
   printf("Error sending data!\n");  
   exit(1);
 
  }
  int asd=ret/1000;
  
 }   
 
 
 close(newsockfd);
 
 close(sockfd);

 
 pthread_exit(NULL);
 return;
}

