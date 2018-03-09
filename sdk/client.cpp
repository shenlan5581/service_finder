#include <unistd.h> 
#include <string.h>
#include <assert.h>
#include "deps/json/json/json.h"
#include "client.h"
#include <pthread.h>

namespace k
{
Sdk* Sdk::client_=nullptr;
string Sdk::server_ip;
string Sdk::server_port; 
int    Sdk::timeout = 0;
using namespace std;

Sdk::Sdk() {
 http = new Curl;
}

Sdk::~Sdk(){
 if(client_ != nullptr)
  delete client_;
  delete http;
} 
Sdk* Sdk::GetInstance()
 {  
      if (client_ == nullptr)
      { 
        client_ = new Sdk;
        return client_;
      }else{
        return client_;
      }
 }
 
void Sdk::SetServerIPandPort(string IP,int port) {
 Sdk::server_ip = IP;
 Sdk::server_port =to_string(port);
}   
int Sdk::Register(string service_name,string addr, string port){
     string   uri,result;
     Json::Reader reader;   
     Json::Value  root,ar;
     int  id ;pthread_t pid;
     uri=server_ip+":"+server_port+"/service_finder?operate=register&service_name="+service_name+"&ip="+addr+"&port="+port+"";
     result = http->Get(uri);
  if (!reader.parse(result,root)) {
        return -1; 
     }   
  if (root["message"].asString() == "success") {
     timeout =atoi((root["timeout"].asString()).c_str());    
     id = atoi((root["servers"][0]["id"].asString()).c_str()); 
     int * sid =new int;
     *sid  = id;
     pthread_create(&pid,nullptr,KeepAlive,sid);
     save_pid_[id]=pid;
        return (id);
  } else {
        return -1;
      }
}
int  Sdk::Unregister(int service_id){
     string   uri,result;
     Json::Reader reader;   
     Json::Value  root,ar;
     string id = std::to_string(service_id);
      uri=server_ip+":"+server_port+"/service_finder?operate=unregister&id="+id+"";
      result = http->Get(uri);   
    if (!reader.parse(result,root))
    {     
        return -1; 
    }   
   if (root["message"].asString() == "success")
   { 
     Pid::iterator  p;
     pthread_t pid =  (p=save_pid_.find(service_id))->second;
     pthread_cancel(pid);
     save_pid_.erase(p);  
     return 1;
   } else {
   return -1;
   }
   return -1;
  }
JSON Sdk::Query(string service_name) {
     string   uri,result;
     Json::Reader reader;   
     Json::Value  root,ar;
      uri=server_ip+":"+server_port+"/service_finder?operate=query&service_name="+service_name+"";
     result = http->Get(uri);  
  if(!reader.parse(result,root)) {
        result.clear();
        return result; 
    }   
   if( root["message"].asString() == "success") {
        return  result;
   } else {
        cout<<result<<endl; //test
        result.clear();
        return result; 
   }
} 
void * Sdk::KeepAlive(void* service_id){   
      Curl curl;
      string id  = to_string(*(int *)(service_id));
      string uri =server_ip+":"+server_port+"/service_finder?operate=update&id="+id+"";
      delete (int*)service_id;
 while (1){
    curl.Get(uri);  
    sleep(timeout);
 } 
return NULL;
}
} //namespace k end
