#include <stdio.h>
#include "http_server.h"
#include <functional>
#include <string>
#include <iostream>
#include <json/json.h>
using namespace std;
using namespace placeholders;

class TestHandler : public http::IHandler {
public:
    void handle(struct evhttp_request *req) 
    {
        struct evbuffer *buf;
        buf = evbuffer_new();


	Json::Value root;
	root["ret"] = 0;
	root["message"] = "ok";
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
    void handle(struct evhttp_request *req) 
    {
        struct evbuffer *buf;
        buf = evbuffer_new();
        string resultURL = "this is default handler\n";
        evbuffer_add_printf(buf, resultURL.c_str());
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
        evbuffer_free(buf);    
    }    
};

int main(void) {
    http::Server server;
    server.Handle("/test", new TestHandler());
    server.ListenAndServe(1811, 2, 1024, new DefaultHandler());
}
