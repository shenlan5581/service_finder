
#ifndef SERVE_H
#define SERVE_H
#include "http_server.h"
#include "database.h"
#include "msg.h"
namespace k
{

class serve : public http::IHandler
{
 public:
 virtual void handle(struct evhttp_request *req);

 private:
     void  reg(uri *); 
     void  find(uri *);
     void  dle(uri *);
     void  update(uri *);
    
    database *mysql;  
};
}


#endif