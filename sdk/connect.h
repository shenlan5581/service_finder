
#ifndef CONNECT_H
#define CONNECT_H

#include <string>
#include <stdio.h> 
#include <string.h>
#include <iostream>

#define  SERVER_ADDR  "192.168.1.104"
#define  PORT          80 
#define  MSGLEN        512

#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


namespace k

{ 
    using std::string;
   class Connect 
  {
   public:
     Connect(); 
     int   send_msg(string msg);
     int   recv_response(string * msg){ *msg="HTTP/1.1 200 OK"; };
     int   get_fd(){};
   private:
      int sockfd;
      int create_socket(){};
  }; 
}

#endif