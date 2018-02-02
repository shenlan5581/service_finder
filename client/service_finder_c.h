/*
*   sdk for servuce_finder_client
*         
*/
#ifndef SERVICE_FINDER_C_H
#define SERVICE_FINDER_C_H
 
#include <string>
#include <pthread.h>
#include <iostream>
#include "connect.h" 
 



namespace k
{ 
  
using std::string;
  class service_finder_c  
{
  public:
      int _register (const string service_name,const string addr,const string port);
      int unregister(const string service_name,const string addr,const string port);
      string query  (const string service_name);
      int keep_alive(const string service_name,const string addr,const string port);	
 
  private:
      static void * heartbeat(void*);
      string http_transformaction(string action, const string service_name,const string addr,const string port);
      Connect    transport; 
      string get_status(const string* response);   

      pthread_t  tid;
};

 

}
 
#endif
