

#include "service_finder_c.h"
 
k::service_finder_c FIND;
  
namespace k
{

   int service_finder_c::_register(string service_name,string addr,string port) 
   {    
        int n;
        string msg ;
        string response;
       if(service_name.length() == 0 || addr.length() == 0)
          return -1;          
        msg =  http_transformaction("register",service_name, addr,port);     
        transport.send_msg( msg);
        response =transport.recv_response(&response);
     if(get_status(&response) != "200") 
         return -1;
      else
         return 0; 
   } 

      int service_finder_c::unregister(const string service_name,const string addr,string port) 
   { 
        int n;
        string msg ;
        string response;
      
       if(service_name.length() == 0 || addr.length() == 0)
          return -1;
          
        msg = http_transformaction("unregister",service_name, addr,port); 
        transport.send_msg(msg);
     if(get_status(&response) != "200") 
         return -1;
      else
         return 0; 
   }    
      string service_finder_c::query(const string service_name)
   { 
        int n;
        string msg ;
        string response; 

       if(service_name.length())
          return  NULL;
       
        msg = http_transformaction("query",service_name, NULL,NULL);
        transport.send_msg(msg);
       
      if(get_status(&response) != "200") 
         return  NULL;   
        else{
               //匹配空行

        }  
        return response; 
   } 
 
   int keep_alive(const string service_name,const string addr,string port) 
{
   
}

  
string service_finder_c::http_transformaction(string action,const string service_name,const string addr,const string port)
{
        string http;
        http = http +"GTE /server_finder/"+action+"?";
        http = http +"service_name="+service_name;  
        if(addr.length() != 0)
        http = http +"&ip="+addr;
        if(addr.length() != 0)
        http = http +"&port="+port;
        http = http +" HTTP/1.0\n"; 
        http = http +"Accept：text/json\n";
        http = http +"\n";
        http = http +"\0";

        return http;
}
 
string service_finder_c::get_status(const string * response)
{    
     int n;
     string status;
     n = (*response).find(' ',0);
     status = (*response).substr(n+1,3);
     return status; 
    
}

 
} //namespace k end