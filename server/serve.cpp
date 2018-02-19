


#include "serve.h"
#include <string>
#include <iostream>
 
using namespace std;  
namespace k
{
 
  
string serve::time = TIME_FOR_NEAR_TO_LAST_UPDATA; 
int serve::create_connection()
{    
      sql = new mysql; 
      CONNECT;
 
      int e = sql->connect(&i);
      if(e)
      return 1;
      else return 0;
}

int serve::analyze( string *url,item * info)   // url
{   
  int end=0;
      string::size_type b,z;
      string key;
      string value;
      b=url->find("?");
      z=b;
  while(1)    //key and value
      {        
            b=z;    
            z =url->find("=",b);      
            if(z == string::npos)
            return 0;
            else 
            key = url->substr(b+1,z-b-1);
            //test  cout<<"key:"<<key<<"  "; 
            b = z;                      
            z = url->find("&",b);
            if(z == string::npos)          
              {
                  z = url->find("\0",b);
                if(z == string::npos)        
                  return -1;
                  else                        
                    { 
                      value= url->substr(b+1,z-b-1);
                      end =1;
                    }
              }else
                 value= url->substr(b+1,z-b-1);

                 //test  cout<<"value:"<<value<<endl;
                 const string k= key;
                    (*info)[k]=value;
               if(end == 1)
               break;     
      } 
   // std::cout << service_name<<ip<<port<<id; //test  
  return 1; 
}
 
 void serve_reg:: handle(struct evhttp_request *req)
 {  
  pthread_mutex_lock(&mutex_mysql);
       std::string url = evhttp_request_get_uri(req);    //get url
       assert(create_connection()); 
  
       Json::Value root;  
       item info,result;
       item::iterator p;
       analyze(&url,&info);     
       assert((p=info.find("service_name")) != info.end());
       assert((p=info.find("ip")) != info.end());
       assert((p=info.find("port")) != info.end());
       info["table_name"]=TABLE; 
 
       result=sql->insert(&info);  //  mysql
 
       delete sql;
pthread_mutex_unlock(&mutex_mysql);
     
       p=result.find("state");
         string  state = (p=result.find("state"))->second;
         root["message"]= state;
         root["ret"] = 0;
       if(  state == "success") 
        { 
          root["servers"][0]["id"] =(p=result.find("id"))->second; 
        }
        else  
        { 
          root["servers"][0]["id"] ="-1";
        }
          root["servers"][0]["service_name"] = "-1";
          root["servers"][0]["ip"] = "-1";
          root["servers"][0]["port"] = "-1";
       struct evbuffer *buf;
       buf = evbuffer_new();
       Json::FastWriter writer;
       std::string output = writer.write(root);
       evbuffer_add_printf(buf, output.c_str());
       evhttp_send_reply(req, HTTP_OK, "OK", buf);
       evbuffer_free(buf);  
    
 
 }
 
 void serve_unreg::handle(struct evhttp_request *req)
 {
       std::string url = evhttp_request_get_uri(req);    //get url
pthread_mutex_lock(&mutex_mysql);
       assert(create_connection());
  
       Json::Value root;  
       item info,result;
       item::iterator p;
       analyze(&url,&info);     
       assert((p=info.find("id")) != info.end());
       info["table_name"]=TABLE; 

       result=sql->del(&info);  //  mysql
       delete sql;
pthread_mutex_unlock(&mutex_mysql);
       p=result.find("state");

       string  state = (p=result.find("state"))->second;

          root["message"]= state;
          root["ret"] = 0;

       if(  state == "success") 
        { 
          root["servers"][0]["id"] =0;
        }
        else  
        { 
          root["servers"][0]["id"] ="-1";
        }
          root["servers"][0]["service_name"] = "-1";
          root["servers"][0]["ip"] = "-1";
          root["servers"][0]["port"] = "-1";
       struct evbuffer *buf;
       buf = evbuffer_new();
       Json::FastWriter writer;
       std::string output = writer.write(root);
       evbuffer_add_printf(buf, output.c_str());
       evhttp_send_reply(req, HTTP_OK, "OK", buf);
       evbuffer_free(buf);  
       
   
 }

  void serve_find::handle(struct evhttp_request *req)
 {
       std::string url = evhttp_request_get_uri(req);    //get url
pthread_mutex_lock(&mutex_mysql);
       assert(create_connection());
   
       Json::Value root;  
       item info;
       v_result  v_ret;
       item::iterator p;
       analyze(&url,&info);     
       assert((p=info.find("service_name")) != info.end());
       info["table_name"]=TABLE;
       info["time"]=time;
        
           v_ret = sql->find(&info);  //  mysql
            delete sql;
pthread_mutex_unlock(&mutex_mysql);
          item result = v_ret[0];
          p=result.find("state");
       string  state = (p=result.find("state"))->second;
         root["message"]= state;
  if(state == "success") 
    {     
           root["ret"] = v_ret.size()-1;
    for(int i=1;i<v_ret.size();++i) 
    {     
      root["servers"][i-1]["id"] = (p=v_ret[i].find("id"))->second;
      root["servers"][i-1]["service_name"] = (p=v_ret[i].find("service_name"))->second;
      root["servers"][i-1]["ip"] = (p=v_ret[i].find("ip"))->second;
      root["servers"][i-1]["port"] =(p=v_ret[i].find("port"))->second;
    }
   }  
    else  
        { 
          root["ret"] = 0;
          root["servers"][0]["id"] ="-1";
          root["servers"][0]["service_name"] = "-1";
          root["servers"][0]["ip"] = "-1";
          root["servers"][0]["port"] =" -1";
        }    
       struct evbuffer *buf;
       buf = evbuffer_new();
       Json::FastWriter writer;
       std::string output = writer.write(root);
       evbuffer_add_printf(buf, output.c_str());
       evhttp_send_reply(req, HTTP_OK, "OK", buf);
       evbuffer_free(buf);  
      
 
 }

void serve_update::handle(struct evhttp_request *req)
 {
       std::string url = evhttp_request_get_uri(req);    //get url
pthread_mutex_lock(&mutex_mysql);
       assert(create_connection()); 
 
       Json::Value root;  
       item info,result;
       item::iterator p;
       analyze(&url,&info);     
       assert((p=info.find("id")) != info.end());
       info["table_name"]=TABLE; 
 
       result=sql->update(&info);  //  mysql
       delete sql;
pthread_mutex_unlock(&mutex_mysql);
       p=result.find("state");
       string  state = (p=result.find("state"))->second;

          root["message"]= state;
          root["ret"] = 0;

       if(  state == "success") 
        { 
          root["servers"][0]["id"] =(p=result.find("id"))->second;
        }
        else  
        { 
          root["servers"][0]["id"] ="-1";
        }
          root["servers"][0]["service_name"] = "-1";
          root["servers"][0]["ip"] = "-1";
          root["servers"][0]["port"] = "-1";
       struct evbuffer *buf;
       buf = evbuffer_new();
       Json::FastWriter writer;
       std::string output = writer.write(root);
       evbuffer_add_printf(buf, output.c_str());
       evhttp_send_reply(req, HTTP_OK, "OK", buf);
       evbuffer_free(buf);  
     
      
    }

void serve_monitor::handle(struct evhttp_request *req)
 {
     pthread_t pid;
     int  r;
 pthread_mutex_init(&mutex_mysql,NULL);
     r = pthread_create(&pid,NULL,monitoring,this);
     assert(r == 0);
     //pthread_join(pid, NULL);
     
    }
void * serve::monitoring(void * a)
 {   
 
   serve_monitor *monitor = (serve_monitor *)a;
   while(1)
   {
        
   pthread_mutex_lock(&monitor->mutex_mysql);      
    {      
       sleep(TIME_FOR_MONITOR);
       assert(monitor->create_connection());   
       item info,result;
       item::iterator p;
       info["table_name"] = TABLE; 
       info["time"] =time;
       result=monitor->sql->del_invalid(&info);  //  mysql
       p=result.find("state");
       cout<<"monitoring "<<p->second<<endl;
       delete monitor->sql;
     } 
   pthread_mutex_unlock(&monitor->mutex_mysql);
    
   }
 }
}

 
