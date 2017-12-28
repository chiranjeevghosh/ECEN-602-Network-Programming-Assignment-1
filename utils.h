// ********************** Utilities Code ************************************
// Author        :      Chiranjeev Ghosh (chiranjeev.ghosh@tamu.edu)
// Organization  :      Texas A&M University, CS for ECEN 602 Assignment 1
// Description   :      Contains writen() and readline() function definitions
// Last_Modified :      09/22/2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int MAX_STR_LEN = 120;


// ********************** writen() function definition *************************

int writen(int sock_desc, char *buf, int len_str)
{
  int write_return_val;

  write_checkpoint:
    write_return_val = write(sock_desc, buf, (len_str + 1));

  if (write_return_val < 0)
  {
    if (errno == EINTR)
      goto write_checkpoint; 
    return (-1);
  }
  else
    return (len_str);
}


// ********************** readline() function definition ***********************

static int read_cnt;
static char *read_ptr;
static char read_buf[120];

int custom_read(int sock_desc, char *ptr)
{

//printf("RL read count: %d \n", read_cnt);
    if (read_cnt <= 0) {
      read_checkpoint:
      //printf("chktpt read count: %d \n", read_cnt);
	    read_cnt = read(sock_desc, read_buf, MAX_STR_LEN);
      if (read_cnt < 0) {
        if (errno == EINTR)
          goto read_checkpoint;
          return (-1);
      } else if (read_cnt == 0)
          return (0);
      read_ptr = read_buf;
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return (1);
}

int readline(int sock_desc, char *buf,  int max_len)
{
  char    lone_char;
  int     rc, i;

  //ptr = vptr;
    
  for (i = 0; i<(max_len - 1); i++) {
    rc = custom_read(sock_desc, &lone_char);
    if (rc == 1) {
        *buf++ = lone_char;
        if (lone_char  == '\n')
          break;          // Break at newline
    } 
    else if (rc == 0) {
      *buf = 0;
      return (i);         // EOF
    } 
    else
      return (-1);        
  
  *buf  = 0;   
  return (i+1);               // Taking null character at the end into account
  }
}



int err_sys(const char* x)    // Error display source code
{ 
    perror(x); 
    exit(1); 
}






