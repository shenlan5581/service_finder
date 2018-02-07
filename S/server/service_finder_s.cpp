

#include "service_finder_s.h"


namespace k
{
   string service_finder_s::response(int sockfd)
{  
    char msg[MSGLEN];
    string message;
 
    if( get_msg(sockfd,(char *)&msg) == -1)
 return "ERROR";
    message = msg;

    http_request   req(message);    //创建 http_request 对象
  /*
  if(req.request_type == "register")
     return  _register(&req);
  if(req.request_type == "unregister")
     return  unregister(&req);
  if(req.request_type == "query")
     return  query(&req);*/

  return "ERROR";  
}
 

 





int   service_finder_s::get_msg(int sockfd,char* msg)
{ 
    using namespace std;
      char c;
      int i,n,len;
      char buf[MSGLEN];
      memset(buf,0,MSGLEN);
    for(i = 0; i<MSGLEN;i++)
    {
      n=read(sockfd,&c,1); 
      if(n==0)
      return -1;
      if(c == '\n')
      {    
           buf[i] =c;
           n = read(sockfd,&c,1);
           if(c == '\n')
           {
           buf[i] = c;   
           break;
           }      
       }
       buf[i]=c;
    }   
    strcpy(msg,buf);
   return 0;
 }

 
}//end namespace
 