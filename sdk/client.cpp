

#include "client.h"
#include <unistd.h> 
#include <string.h>
#include <assert.h>
#include "deps/json/json/json.h"
namespace k
{
 static int global_respone_state=-1;


  using namespace std;
Sdk::Sdk()
{
 execute = new EvhttpHandler;
}

Sdk::~Sdk(){
 if(client != NULL)
  delete client;
  delete execute;
} 
Sdk* Sdk::client=NULL; 
  Sdk* Sdk::GetInstance()
 {  
      if(client==NULL)
      { 
        client = new Sdk;
        return client;
      }else{
        return  client;
      }
 }
 
 void Sdk::SetServerIPandPort(string IP,int port)
{
   execute->SetServerIPandPort(IP,port);
}   

 
int Sdk::Register(string service_name,string addr, string port){
     string   uri,result;
     Json::Reader reader;   
     Json::Value  root,ar;

    if(service_name.empty()&&addr.empty()&&port.empty())
      return -1;
     
      uri="/register?service_name="+service_name+"&ip="+addr+"&port="+port+"";
      global_respone_state = -1;       
      int err = execute->handler(uri);
      if(err==-1)
       return -1;                                     //测试  条件变量？？？
     while(global_respone_state == -1)
     { 
     }
     result = execute->get_result();   
    if(!reader.parse(result,root))
    {     
        return -1; 
    }   
 
   if( root["message"].asString() == "success")
   { 
        int  id ;
        id = atoi((root["servers"][0]["id"].asString()).c_str()); 
        if(execute->HeartBeat_Start(id));
        return id;
   }else{
   return -1;
   }
}

//==================================================

 
int  Sdk::Unregister(int service_id){
  string   uri,result;
     Json::Reader reader;   
     Json::Value  root,ar;
     string id = std::to_string(service_id);
 
    if(id.empty())
      return -1;
     
      uri="/unregister?id="+id+"";
      global_respone_state = -1;   
     
      int err = execute->handler(uri);
      if(err==-1)
       return -1;                                     //测试  条件变量？？？
     while(global_respone_state == -1)
     {
     }
     result = execute->get_result();   
    if(!reader.parse(result,root))
    {     
        return -1; 
    }   
   if( root["message"].asString() == "success")
   { 
       if(execute->HeartBeat_Stop(service_id))
        return 1;
   }else{
   return -1;
   }
   return -1;
  }
 
  json  Sdk::Query(string service_name){
  string   uri,result;
     Json::Reader reader;   
     Json::Value  root,ar;

    if(service_name.empty())
      return "name empty";
     
      uri="/find?service_name="+service_name+"";
      global_respone_state = -1;   
       
      int err = execute->handler(uri);
      if(err==-1)
       return "query failed";                                   
     while(global_respone_state == -1)
     {
     }
     result = execute->get_result();  
    
    if(!reader.parse(result,root))
    {     
        return "result failed"; 
    }   
   if( root["message"].asString() == "success")
   { 
        return  result;
   }else{
     cout<<result<<endl;
   return "message failed";
   }
  }
 
//=====================================================================
  int EvhttpHandler::SetServerIPandPort(string IP,int port){
   server_ip   = IP;
   server_port = port;
  }
 
  int EvhttpHandler::handler(string uri)
{   
 
  {    //libevent 
   
   struct  event_base *      base=event_base_new();  
   //struct  evdns_base *      dns = evdns_base_new(base,1);
   struct  evhttp_request *  request= evhttp_request_new(EventConnection_cb,base);
   if(!request)
   return -1;
   //evhttp_request_set_header_cb(request,SetHeader_cb);   
   evhttp_request_set_chunked_cb(request,EventChunk_cb);
   evhttp_request_set_error_cb(request,EventError_cb);
   struct evhttp_connection * http = evhttp_connection_base_new(base,NULL,server_ip.c_str(),server_port);
   if(!http)
   return -1;  
   evhttp_connection_set_closecb(http,EventClose_cb,NULL);
   evhttp_make_request(http,request,EVHTTP_REQ_GET,uri.c_str());
   event_base_dispatch(base);    
  }
   return 1 ;
}

string EvhttpHandler::get_result(){
  return result;
}

int EvhttpHandler::HeartBeat_Start(int service_id){
     
     pthread_t pid;
    if(service_id < 0)
     {  
        return -1;
     }
     string * id;
     id = new string;             
     *id = to_string(service_id);
     
     pthread_create(&pid,NULL,KeepAlive,id);  
     save_pid[service_id]= pid; 
     return 0;
 
}
int EvhttpHandler::HeartBeat_Stop(int service_id){
      int err;
      pthread_t pid;
    if(service_id < 0)
     {
        return -1;
     }
     PID::iterator iter;
     iter = save_pid.find(service_id);   
     if(iter == save_pid.end())
     {   cout<<"no find pid"<<endl;
     return-1;
     }
     err = pthread_cancel(iter->second);
    if(err == 0)
     return 1;
    
    return -1;
}


void* EvhttpHandler::KeepAlive(void *service_id){   
      string   uri; 
      string  id = *(string *)service_id;
      cout<<id<<endl;
      Sdk* sdk = Sdk::GetInstance();
      EvhttpHandler * e =(EvhttpHandler *)sdk->execute; 
      uri ="/update?id="+id+"";
       
      delete (string*)service_id;
 while(1)
 {
   struct  event_base *      base=event_base_new();  
   //struct  evdns_base *      dns = evdns_base_new(base,1);
   struct  evhttp_request *  request= evhttp_request_new(EventConnection_cb,base);
   if(!request)
   pthread_exit(NULL);
   //evhttp_request_set_header_cb(request,SetHeader_cb);   
   evhttp_request_set_chunked_cb(request,EventHeartbeatChunk_cb);
   evhttp_request_set_error_cb(request,EventError_cb);
   struct evhttp_connection * http = evhttp_connection_base_new(base,NULL,e->server_ip.c_str(),e->server_port);
   if(!http)
   pthread_exit(NULL);
   evhttp_connection_set_closecb(http,EventClose_cb,NULL);
   evhttp_make_request(http,request,EVHTTP_REQ_GET,uri.c_str());
   event_base_dispatch(base);   
   sleep(TIMEOUT);
   } 
}


void  EvhttpHandler::EventHeartbeatChunk_cb(struct evhttp_request * req,void*arg)      //chunk
{

   Json::Reader reader;   
   Json::Value  root,ar;
 
   string ret;
   char buf[4096];
   int n = 0;
    struct evbuffer* evbuf = evhttp_request_get_input_buffer(req);    //get message
   memset(buf,0,4096);
   while ((n = evbuffer_remove(evbuf,buf,4096)) > 0) 
   {   
        ret=ret+buf;    
        memset(buf,0,4096);  
   } 
    
    if(!reader.parse(ret,root))
    {     
        cout<<"heartbeat-response error"<<endl; 
    }   
   if ( root["message"].asString() == "success")
   { 
        cout<<"heartbeat success id:"<<root["servers"][0]["id"].asString()<<endl;
   }else{
       cout<<"heartbeat update failed"<<endl; 
   }

 

   event_base_loopexit((struct event_base*)arg, NULL);
}

void EvhttpHandler::EventChunk_cb(struct evhttp_request * req,void *arg)   //chunk
{  
   Sdk* sdk = Sdk::GetInstance();
   EvhttpHandler * e =(EvhttpHandler *)sdk->execute;
   string ret;
   char buf[4096];
   int n = 0;
    struct evbuffer* evbuf = evhttp_request_get_input_buffer(req);    //get message
   memset(buf,0,4096);
   while ((n = evbuffer_remove(evbuf,buf,4096)) > 0) 
   {   
        ret=ret+buf;    
        memset(buf,0,4096);  
   } 
   e->result=ret;
   event_base_loopexit((struct event_base*)arg, NULL);
   global_respone_state = 1;
 } 
 

 void EvhttpHandler::EventConnection_cb(struct evhttp_request * pa1,void*){
   //cout<<"connectcb"<<endl;
 }
 void  EvhttpHandler::EventError_cb(enum evhttp_request_error,void*arg){

   cout<<"errorcb"<<endl;
  // event_base_loopexit((struct event_base*)arg, NULL);
 }

 void EvhttpHandler::EventClose_cb(struct evhttp_connection * pa1,void*arg){
  cout<<"closecb"<<endl;
 
   //event_base_loopexit((struct event_base*)arg, NULL);
 } 
 
} //namespace k end

//===============================================
 
 