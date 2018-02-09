
#ifndef SERVE_H
#define SERVE_H
#include <assert.h>
#include "http_server.h"
#include "database.h"
#include "msg.h"
namespace k
{

class serve : public http::IHandler
{
 public:
 virtual void handle(struct evhttp_request *req)=0;

 protected:
    database   *sql;  
    int analyze( string *url,item * info);
           ~serve();

 };
 
class serve_reg:public serve
{
virtual void handle(struct evhttp_request *req);
};
class serve_unreg:public serve
{
virtual void handle(struct evhttp_request *req);
};
class serve_find:public serve
{
virtual void handle(struct evhttp_request *req);
};
class serve_update:public serve
{
virtual void handle(struct evhttp_request *req);
};
 
}





#endif