/*
uri 
/service_finder?operate=[...]&[...]=[....]... ...
operate:register     service_name=xx&ip=xx&port=xx
        unregister   id=xx
        query        service_name=xx
        update       id=xx
*/
#pragma once

#include <assert.h>
#include <string>
#include <unistd.h>
#include "database.h"
#include "./lib/json/json/json.h"
#include "http_server.h"
namespace k {

typedef ret URI ;
class Serve : public http::IHandler {
 public:
	virtual void handle(struct evhttp_request *req);
  static void Clear(void);
 private:
         Json::Value Register(string * url);
         Json::Value UnRegister(string * url);
         Json::Value Query(string * url);
         Json::Value Update(string * url);
};
} //namespace
