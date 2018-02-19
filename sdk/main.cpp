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
#include  "client.h"
#include  <assert.h>
#include  <unistd.h>


using namespace std;
 

int main()  //test
{ 
    int id1, id2 ,err, i;
    k::Sdk * sdk;
    string   ret; 
    int  pot=10;

  for(i=0;i<1000000;i++)
    {
    sdk=k::Sdk::GetInstance();
    sdk->SetServerIPandPort("127.0.0.1",80); 
  
    id1 = sdk->Register("http","192.168.1.101","80");   //register
    cout<<"register:"<<id1<<endl; 
    id2 = sdk->Register("http","192.168.1.102","80");
    cout<<"register:"<<id2<<endl;
    
    ret = sdk->Query("http");                          //find    
    cout<<"find:"<<ret<<endl; 
    sleep(10);
    err =  sdk->Unregister(id1);      
    assert(err);
    cout<<"unregister:"<<id1<<endl;              //unregister
    err =  sdk->Unregister(id2);      
    assert(err);
    cout<<"unregister:"<<id2<<endl;
    }
}

 
