





#include "connect.h"
#include <arpa/inet.h>

extern  k::service_finder_s S;
namespace k{  
 
 Connect::Connect()     
 {  
    int    err;  
    struct sockaddr_in addr;
     addr.sin_family = AF_INET;
     addr.sin_port = htons(PORT);
     addr.sin_addr.s_addr = htonl(INADDR_ANY);
     listen_fd= socket(AF_INET, SOCK_STREAM, 0);
    

     err = bind(listen_fd,(struct sockaddr *)&addr,sizeof(addr));
     if(err <0)
     {std::cout <<"bind err\n"<<std::endl; 
       _exit(0);    
     }
 }
  

void Connect::Listen() 
{  
    sockaddr_in cliaddr;
    socklen_t   clilen;
    int connfd;
    listen(listen_fd,MAX_CONNECT); 
    while(1)
   {
     connfd = accept(listen_fd, (struct sockaddr *)&cliaddr, &clilen); 
       
     S.response(connfd);
    
   }
} 

    
}

  







 