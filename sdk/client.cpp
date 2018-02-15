

#include "client.h"
#include <unistd.h> 
#include <string.h>

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
   if( root["message"].asString() == "successd")
   { 
        int  id ;
        id = atoi((root["servers"][0]["id"].asString()).c_str()); 
        return id;
   }else{
   return -1;
   }
}

//==================================================

 
int  Sdk::Unregister(string id){
  string   uri,result;
     Json::Reader reader;   
     Json::Value  root,ar;

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
   if( root["message"].asString() == "successd")
   { 
        return 1;
   }else{
   return -1;
   }
  }
 
  json  Sdk::Query(string service_name){
  string   uri,result;
     Json::Reader reader;   
     Json::Value  root,ar;

    if(service_name.empty())
      return "no";
     
      uri="/find?service_name="+service_name+"";
      global_respone_state = -1;   
       
      int err = execute->handler(uri);
      if(err==-1)
       return "no";                                     //测试  条件变量？？？
     while(global_respone_state == -1)
     {
     }
     result = execute->get_result();  
    
    if(!reader.parse(result,root))
    {     
        return "no"; 
    }   
   if( root["message"].asString() == "successd")
   { 
        return  result;
   }else{
   return "no";
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
   cout<<"connectcb"<<endl;
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
 
 