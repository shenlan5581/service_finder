


#ifndef SERVICE_FINDER_S_H
#define SERVICE_FINDER_S_H

#include <string>
#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "http_request.h"


#define MSGLEN 1024 

namespace k
{
    using std::string;
     
 class service_finder_s
  {
   public:
        string response(int sockfd);     //处理响应
   public:
 /*     string  _register(http_request*){};
        string  unregister(http_request*){};
        string  query(http_request*){};
        int  keep_alive(int sock,http_request*){}; 
*/ 

      int  get_msg(int sockfd,char* msg);

  };

}
#endif