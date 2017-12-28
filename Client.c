// ************************************ Client Code *********************************************
// Author        :      Chiranjeev Ghosh (chiranjeev.ghosh@tamu.edu) 
// Organisation  :      Texas A&M University, CS for ECEN 602 Assignment 1
// Description   :      Establishes an IPv4 socket, takes port number and IP Addr specified from 
//                      command line to connect to a server, writes a message to the server and 
//                      waits to hear back the same message (echo) from the server.
// Last_Modified :      09/22/2017


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <utils.h>



int main(int argc,char *argv[])
{
  int sockfd, inet_p2n_ret, conn_ret, n;
  char sendline[MAX_STR_LEN];
  char recvline[MAX_STR_LEN+1];
  int ret = 0;
  int port_number ;
  char *p;
  long conv_arg_to_int = strtol(argv[1], &p, 10);

  if (argc != 3){
    err_sys ("USAGE: ./echo <Port_Number> <IP_Address>");
    return 0;
  }

  port_number = conv_arg_to_int;
  
  
  struct sockaddr_in servaddr;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if (sockfd < 0)
    err_sys ("ERR: Socket Error");

  bzero(&servaddr,sizeof servaddr);
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(port_number);
  inet_p2n_ret = inet_pton(AF_INET,argv[2],&(servaddr.sin_addr));
  if (inet_p2n_ret <= 0)
    err_sys ("ERR: inet_pton error");

  conn_ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  if (conn_ret < 0)
    err_sys ("ERR: Connect Error");

  while(1)
  {
    bzero( sendline, MAX_STR_LEN);
    bzero( recvline, MAX_STR_LEN + 1);
    fgets(sendline,MAX_STR_LEN,stdin); /*stdin = 0 , for standard input */
    writen(sockfd,sendline,strlen(sendline));
    printf ("CLIENT: Writing message to server \n");
    //readline(sockfd, recvline, MAX_STR_LEN);
    ret = read(sockfd, recvline, MAX_STR_LEN);
    recvline [ret] = '\0';
    ret = 0;
    printf ("CLIENT: Reading ECHOED message from server %s \n", recvline);
    
    
  }

  return 0;

}
