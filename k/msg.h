

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
class uri 
{ 
public:
    string message;  
    string request_type; 
    string service_name;
    string ip;
    string port;
    string id;
    uri(string msg);       // 从msg 解析
    uri(string request_type,  string service_name, string ip,  string port);
   
private:
    int create_msg();  //合成 http  消息 
    int analyze();     //解析 http  报文
 
 };
}
#endif