// ************************************ Server Code *********************************************
// Author        :      Chiranjeev Ghosh (chiranjeev.ghosh@tamu.edu) 
// Organisation  :      Texas A&M University, CS for ECEN 602 Assignment 1
// Description   :      Establishes an IPv4 socket, takes port number specified from command line
//                      to bind, listen and accept multiple client connections simultaneously. 
//                      Once connection is established, message received is echoed back to the
//                      client.
// Last_Modified :      09/22/2017


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <utils.h>



int main(int argc, char *argv[])
{
  char temp_str;
  char str[MAX_STR_LEN];
  int sockfd, comm_fd, bind_fd, listen_fd;	
  int port_number ;
  char *p;
  long conv_arg_to_int = strtol(argv[1], &p, 10);
  
  if (argc != 2){
    err_sys ("USAGE: ./echos <Port_Number>");
    return 0;
  }
  
  port_number = conv_arg_to_int;
  int pid;
  struct sockaddr_in servaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    err_sys ("ERR: Socket Error");

  bzero( &servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);
  servaddr.sin_port = htons(port_number);
  bind_fd = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  if (bind_fd < 0)
    err_sys ("ERR: Bind Error");
  listen_fd = listen(sockfd, 10);
  if (listen_fd < 0)
    err_sys ("ERR: Listen Error");
  while(1)
  {
    comm_fd = accept(sockfd, (struct sockaddr*) NULL, NULL);
    pid = fork();
    if (pid > 0) {            // Parent
      printf("SERVER: This is the parent for %d\n", pid);	
    }
    else if (pid == 0){                     // Child
      while (1)
      {
        bzero(str, MAX_STR_LEN);
        printf("SERVER: This is the child process \n");
        read(comm_fd,str,MAX_STR_LEN);
        printf ("SERVER: Reading message from client \n");
        printf("SERVER: Echoing back: %s \n",str);
        writen(comm_fd, str, strlen(str)+1);
      
      }
    
    }
    else {                                  // pid = -1
      printf("ERR: fork() returns error signal with errno: %d\n ", errno);
      break;
    }
  }
}

