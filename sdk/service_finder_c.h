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
          service_finder_c (string server_addr,string port);
  virtual    ID    register(const string service_name,const string addr,const string port)=0;
  virtual    int   unregister (ID)=0;
  virtual    json  query(const string service_name)=0;
};

 

}
 
#endif
