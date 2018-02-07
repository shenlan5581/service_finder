
#ifndef CONNECT_H
#define CONNECT_H

#include <string>
#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "main.h"


#include <netinet/in.h>
#include <netdb.h> 
#include "service_finder_s.h"

namespace k
{ 
   using std::string;
   class Connect 
  {
   public:
     Connect(); 
      
      void Listen();
      

   private:
      int  listen_fd;
    
  }; 
}

#endif
