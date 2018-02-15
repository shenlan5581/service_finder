
#ifndef SERVE_H
#define SERVE_H

#include <assert.h>
#include "http_server.h"
#include "database.h"
#include  "./lib/json/json/json.h"  
#include <pthread.h> 
#include <unistd.h>
namespace k
{

// set mysql  info       username and password
 #define CONNECT          k::item i; \
                          i["addr"]="127.0.0.1";\
                          i["user"]="root";\
                          i["password"]= "xingke";\
                          i["database_name"]="service_finder";


#define TABLE           "service_table"  // datebase table name

#define TIME_FOR_MONITOR                120
#define TIME_FOR_NEAR_TO_LAST_UPDATA   "30"          
 

class serve : public http::IHandler
{
 public:
 virtual void handle(struct evhttp_request *req)=0;
    static string time;   
 protected:
    mysql   *sql;  
    int analyze(string *url,item * info);
    int create_connection();

    pthread_mutex_t mutex_mysql ;
    static void*monitoring(void *); 
    
 };

 

class serve_reg:public serve
{
public:
    virtual void handle(struct evhttp_request *req);
};
class serve_unreg:public serve
{
public:
    virtual void handle(struct evhttp_request *req);
};
class serve_find:public serve
{
public:
    virtual void handle(struct evhttp_request *req);
};
class serve_update:public serve
{
public:
    virtual void handle(struct evhttp_request *req);
};
class serve_monitor:public serve
{
public:
    virtual void handle(struct evhttp_request *req);
}; 
 
}
 
 
#endif
