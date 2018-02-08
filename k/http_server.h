#pragma once
#include <event.h>
#include <evhttp.h>
#include <functional>
#include <map>
#include <string>

namespace http {

class IHandler {
 public:
  virtual ~IHandler() {}
  virtual void handle(struct evhttp_request *req) = 0;
};    //lost 


class Server {
 public:
  Server() {}
  ~Server() {}

  void Handle(const std::string &uri, IHandler *handler);

  int ListenAndServe(int port, int nthreads, int backlog, IHandler *handler);
      //create pthreads and run even_dispatch
 private:
  int ensure_listen(int port, int backlog);  //make_socket  return nfd;
  static void event_cb(struct evhttp_request *req, void *arg);//??
  static void *event_dispatch(void *arg);  //  
                                
 private:
  std::map<std::string, IHandler *> mux_;   //witch one? 
  IHandler *default_handler_;
};
}
