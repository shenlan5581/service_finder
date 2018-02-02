





#include "connect.h"
#include <arpa/inet.h>


namespace k{

 Connect::Connect()    
 {  
    struct sockaddr_in servaddr;    
    int err, n, i;                             //错误测试码
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  // 套接字 
    //创建服务器地址
    servaddr.sin_family = AF_INET;     
    servaddr.sin_port = htons(PORT);   
    inet_pton(AF_INET, SERVER_ADDR, &servaddr.sin_addr);
    //建立链接
    err = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (err != 0)
    {    
        std::cout << "[connect] can‘t  connect server"<<std::endl;
        sockfd = -1;
    } 
    else
    {
        std::cout << "[connect] connecting-->server"<<std::endl; //成功链接
        
    }
 }


int Connect::send_msg(string msg) 
{  
using namespace std;
      int n,len;
      len = 0;
      char buf[MSGLEN];
      memset(buf,0,MSGLEN);
      strcpy(buf,msg.c_str());
    
 
      cout<<msg<<endl;
      while(1) 
      {     
           n = write(sockfd,buf,msg.length());
           len = len+n;
           if(len ==msg.length())
           break; 
      }
      cout<<"end"<<endl;
      return 0;
} 
   
}

  







 