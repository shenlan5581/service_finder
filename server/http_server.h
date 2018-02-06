#pragma once
#include <functional>
#include <string>
#include <map>
#include <event.h>
#include <evhttp.h>

namespace http {

    class IHandler {
    public:
        virtual ~IHandler() {}
        virtual void handle(struct evhttp_request *req) = 0;
    };

    class Server {
    public:
        Server(){}
        ~Server(){}

        void Handle(const std::string& uri, IHandler *handler);

        int ListenAndServe(int port, int nthreads, int backlog, IHandler *handler);
        
    private:
        int ensure_listen(int port, int backlog);
        static void event_cb(struct evhttp_request *req, void *arg);
        static void* event_dispatch(void *arg);
    private:
        std::map<std::string, IHandler*> mux_;
        IHandler* default_handler_;
    };
}
