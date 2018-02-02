

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <iostream>
#include <stdio.h>
#define MSGLEN  1024

namespace k
{
  using std::string;

/*
*   http 协议报的  构建和解析
*/ 
class http_request  
{ 
public:
    string message;  
    string request_type; 
    string service_name;
    string ip;
    string port;
    string k;
 
    http_request(const string msg);       // 从msg 解析
    http_request(const string request_type,const string service_name,const string ip,const string port);
   
private:
    int create_msg();  //合成 http  消息 
    int analyze();     //解析 http  报文
 
};

}
#endif