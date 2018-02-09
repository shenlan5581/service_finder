/*
*
*   test
*
*/


#include <iostream>
#include <string>
using namespace std;

#include "connect.h"
 
int main() 
{
 k::Connect ks;
         string http;
        http = http +"GTE /register?"; 
        http = http +"service_name=web";  
        http = http +"&ip=192.168.1.109" ;
        http = http +"&port=80";
        http = http +" HTTP/1.1\n"; 
        http = http +"Accept：text/json\n";
        http = http +"\n";
        http = http +"\n";
        http = http +"\0";
      ks.send_msg(http);
 
  
}
