/*
*
*   test
*
*/


#include  <iostream>
#include  <string>
#include  "./deps/libevent/include/event.h" 
#include  "./deps/libevent/include/evhttp.h" 
#include  "./deps/libevent/include/evdns.h" 
#include "client.h"


using namespace std;
/*
void  EventConnection_cb(struct evhttp_request * pa1,void*)  //executed  when the request completed or an error occurred 
{
 cout<<"cb1"<<endl;
}
int SetHeader_cb(struct evhttp_request * pa1,void*)   //->>set header
{
 //struct evkeyvalq headers = 
 /*err = evhttp_add_header(evhttp_request_get_output_headers(request),"service_name","web");*/
//}
/*
void  EventChunk_cb(struct evhttp_request * pa1,void*)   //chunk
{
   string ret;
   char buf[4096];
   int n = 0;
   struct evbuffer* evbuf = evhttp_request_get_input_buffer(pa1);    //get message
   cout<<"3"<<endl;
   while ((n = evbuffer_remove(evbuf,buf,4096)) > 0) 
   {
        cout<<buf<<endl ;
   }
 
}
void  EventError_cb(enum evhttp_request_error,void*)  //error
{
 cout<<"cb4"<<endl;
}
void  EventClose_cb(struct evhttp_connection * pa1,void*)  //->> close
{
 cout<<"cb5"<<endl;
}


*/


  
int main() 
{ int id;
  k::Sdk * sdk;
  sdk=k::Sdk::GetInstance();
   sdk->SetServerIPandPort("127.0.0.1",80);
  // id = sdk->Register("http","1921.1622w.1d221.11","15");
 /*
  id=sdk->Unregister("25");
  cout<<"last id:"<<id<<endl;*/

  json r=sdk->Query("ftp");
  if(!r.empty())
   cout<<r<<endl;
 // client.SetServerIPandPort("192.168.1.104",80);
//  client.Register("http","192.168.1.11","55");
 

}

 