


#include "serve.h"
#include <string>
#include <iostream>

using namespace std;  
namespace k
{
//set mysql  info
#define CONNECT         k::item i; \
                        i["addr"]="192.168.1.104";\
                        i["user"]="root";\
                        i["password"]= "xingke";\
                        i["database_name"]="service_finder";
#define TABLE           "service_table"



serve::~serve()
{ 
  delete sql;
}
int serve::analyze( string *url,item * info)   // url
{  cout<<*url<<endl;
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
   // std::cout << request_type<<service_name<<ip<<port<<id; //test  
  return 1; 
}
 
  void serve_reg:: handle(struct evhttp_request *req)
 {  
   cout<<"register*****"<<endl;
 
   std::string url = evhttp_request_get_uri(req);    //get url
   cout<<url<<endl;
   cout<<"<handler> register"<<endl;
   sql = new mysql; 
    {                                 // to database
      CONNECT;
      int e = sql->connect(&i);
      assert(e);
    }

       item info,result;
       item::iterator p;
       analyze(&url,&info);
  
       info["table_name"]=TABLE; 
       cout<<"1"<<endl;
       result=sql->insert(&info);
       cout<<"2"<<endl;
       p=result.find("state");
       assert(p !=result.end()); 
       cout<<p->second<<endl;
       p= result.find("id");
       assert(p !=result.end());
       cout<<p->second<<endl;

  

  
 }
 


}













 
 //evhttp_send_reply(req, 200, "OK", NULL);  

/*
void reg::handle(struct evhttp_request *req)
{ 
      cout<<"connect"<<endl;
      std::string  u = evhttp_request_get_uri(req);
     cout<<"uri:"<<u<<endl;
     struct evhttp_uri *decoded = NULL;
     decoded = evhttp_uri_parse(u.c_str());
     string path = evhttp_uri_get_path(decoded);


      cout<<"path"<< path<<endl; 
     // string host= evhttp_uri_get_host(decoded);
   //   cout <<"host"<<host<<endl;
*/
 
/*======================================================================
       k::item i;
       k::item::iterator p;
       k::mysql  sql;
       i["addr"]="192.168.1.108";
       i["user"]="root";
       i["password"]= "xingke";
       i["database_name"]="service_finder";
       sql.connect(&i);
                                              //sql.create_database();  
       i.clear();
       i["table_name"]="service_table";
       i["service_name"]="dns";
       i["ip"]= "192.168.1.80";
       i["port"]="21";
       i= sql.insert(&i);  //ok
       cout << (p=(i.find("state")))->second ;
   
       i.clear();
       i["service_name"]="dns";
       i["table_name"]="service_table";
       i["time"]="40";
       sql.find(&i);   
                                  //ok
       i.clear();
       i["time"]="20";
       sql.del_invalid(&i);       //ok                          
      
       i.clear();
       i["table_name"]= "service_table"; 
       i["id"]="10"; 
       sql.update(&i);           //ok   
       
        i.clear();
       i["table_name"]= "service_table"; 
       i["id"]="10"; 
       sql.del(&i);
                         */              
 
 