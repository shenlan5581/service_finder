 
//#include <mysql++/mysql++.h> nouse
#include <stdio.h>
#include <functional>
#include <iostream>
#include <string>
#include  "http_server.h" 
#include  "serve.h"
#include  "./lib/json/json/json.h"   
#include  "config.h"
#include  "log.h"

using namespace std;
using namespace placeholders;
using namespace k;
class TestHandler : public http::IHandler {
 public:
  void handle(struct evhttp_request *req) {
    struct evbuffer *buf;
    buf = evbuffer_new();
    cout<<"test"<<endl;
    Json::Value root;
   
    root["message"] = "ok";
    root["ret"] = 2;
    root["servers"][0]["id"] = "1";
    root["servers"][0]["ip"] = "127.0.0.1";
    root["servers"][0]["port"] = 80;
   
     
    Json::FastWriter writer;
   
    std::string output = writer.write(root);
    evbuffer_add_printf(buf, output.c_str());
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);  
  }
};

class DefaultHandler : public http::IHandler {
 public:
  void handle(struct evhttp_request *req) {
   /*  mysqlpp::Connection conn(false);
    if (conn.connect("service", "127.0.0.1:3306", "root", "123456")) {
      // Retrieve a subset of the sample stock table set up by resetdb
      // and display it.
      mysqlpp::Query query =
          conn.query("select id,name,ip,port from tb_server");
      if (mysqlpp::StoreQueryResult res = query.store()) {
        cout << "We have:" << endl;
        Json::Value root;
        root["ret"] = 0;
        root["message"] = "ok";

        mysqlpp::StoreQueryResult::const_iterator it;
        int i = 0;
        for (it = res.begin(); it != res.end(); ++it) {
          mysqlpp::Row row = *it;
          cout << '\t' << row[0] << endl;
          root["servers"][i]["id"] = (int)row[0];
          root["servers"][i]["name"] = row[1].c_str();
          root["servers"][i]["ip"] = row[2].c_str();
          root["servers"][i]["port"] = (int)row[3];
          i++;
        }  //JSON
        struct evbuffer *buf;
        buf = evbuffer_new();

        Json::FastWriter writer;
        std::string output = writer.write(root);
        evbuffer_add_printf(buf, output.c_str());
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
        evbuffer_free(buf);
      } else {
        cerr << "Failed to get item list: " << query.error() << endl;
      }
    } else {
      err << "DB connection failed: " << conn.error() << endl;
    } */
  } 
};


namespace k{
  extern ServeLog log;
}
int main(void) {  

    k::log.Start();
    http::Server server;
    serve_monitor monitor;
    monitor.handle(NULL);   
    

  
   server.Handle("/register",  new serve_reg);
   server.Handle("/unregister",new serve_unreg);
   server.Handle("/find",      new serve_find);
   server.Handle("/update",    new serve_update);
   server.Handle("/test",      new TestHandler);

   server.ListenAndServe(80,2, 1024, NULL); 

}

