


#include "http_request.h"

namespace k
{
   
http_request::http_request(const string msg)
{
    message = msg;
    analyze();
 
}    
int http_request::analyze()    //解析协议
{     int end=0;
      string::size_type b,z;
      string key;
      string value;

      b = message.find("/",12);
      if(b == string::npos)
      return -1;
      z = message.find("?",b+1);
      if(b == string::npos)
      return -1;  
      request_type=message.substr(b+1,z-b-1);   //操作类型
  
  while(1)    //key and value
      {    
            b = z;
            z =message.find("=",b);     //查找键
            if(z == string::npos)
            return 0;
            else 
            key = message.substr(b+1,z-b-1);
             
            b = z;                      //查找值
            z = message.find("&",b);
            if(z == string::npos)   // 查找&失败
              {
                  z = message.find(" ",b);
                if(z == string::npos) //查找“ ”也失败“
                  return -1;
                  else           //超找 ” “ 成功
                    { 
                      value= message.substr(b+1,z-b-1);
                      end =1;
                    }
              }else
                 value= message.substr(b+1,z-b-1);
         //赋值 
         if (key == "service_name")
               service_name = value;
         if (key ==  "ip")
               ip =value;
         if (key ==  "port")
                port = value;
         if(end == 1)
         break;     
      } 
    std::cout << request_type<<service_name<<ip<<port<<k;//test  
  return 0; 
}
http_request::http_request(const string request_type,const string service_name,const string ip,const string  port)
{    
#define ADD message=message 


    if(request_type.empty())
         return; 
        ADD+"GTE /server_finder/"+request_type;
   if(service_name=="NULL")
        goto end;
    else
        ADD+"?service_name="+service_name;
   if(ip=="NULL")
        goto  end;
    else
         ADD+"&ip="+ip;
   if(port=="NULL")
         goto end;
    else 
         ADD+"&port="+port;    
      goto end;

  end:
       message = message +" http_request/1.0\n"; 
       message = message +"Accept：text/json\n";
       message = message +"\n";
       message = message +"\0";  
 #undef ADD

}
}  
