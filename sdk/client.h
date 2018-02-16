/*
*   sdk for servuce_finder_client
*         
*/

#ifndef SDK_CLIENT_H
#define SDK_CLIENT_H
 
#include <string>
#include <iostream>
#include <map>
#include <pthread.h>
#include  "./deps/libevent/include/event.h" 
#include  "./deps/libevent/include/evhttp.h" 
#include  "./deps/libevent/include/evdns.h" 
using namespace std; 
 
#define TIMEOUT 8

#define json  string 
typedef map<int,pthread_t> PID;

namespace k {
class  Handler;//

 

 class Sdk  {
public:  
  static Sdk* GetInstance();            
  virtual     void    SetServerIPandPort(string IP,int port);               
  virtual     int     Register(string service_name,string addr, string port);
  virtual     int     Unregister(int service_id);
  virtual     json    Query(string service_name);

             ~Sdk(); 
private:
              Sdk();
 static       Sdk *  client;  
              Handler   * execute;
 friend class EvhttpHandler;
}; 
//============================================================= 
 class Handler
{ 
 public:  
   virtual  int handler(string uri)=0; 
   virtual  int SetServerIPandPort(string IP,int port)=0;
   virtual  string get_result()=0;
   virtual  int HeartBeat_Start(int service_id)=0;
   virtual  int HeartBeat_Stop(int  service_id)=0;
};

 
 class EvhttpHandler :public Handler 
{
public: 
   virtual  int handler(string uri); 
   virtual  int SetServerIPandPort(string IP,int port);
   virtual  string get_result();
   virtual  int HeartBeat_Start(int service_id);
   virtual  int HeartBeat_Stop(int  service_id);
private:   //callback function
   //executed  when the request completed or an error occurred 
   static void  EventConnection_cb(struct evhttp_request * pa1,void*);
   static void  EventChunk_cb(struct evhttp_request * req,void*arg);      //chunk
   static void  EventHeartbeatChunk_cb(struct evhttp_request * req,void*arg);      //chunk
   // static int   SetHeader_cb(struct evhttp_request * pa1,void*);        //->>set http header
   static void  EventError_cb(enum  evhttp_request_error,void*);          //error
   static void  EventClose_cb(struct evhttp_connection * pa1,void*);      //->> close
private: 
static void* KeepAlive(void *id);
   PID     save_pid;
   string  result;
   string  server_ip;
   int     server_port;
private:
   friend class Sdk; 
    EvhttpHandler(){};
   
 }; 

 

}//namespace end
 
#endif     //SDK_CLIENT_H
