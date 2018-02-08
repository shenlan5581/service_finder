#include "http_server.h"
#include <assert.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
using namespace std;
using namespace placeholders;

namespace http {

void Server::Handle(const std::string &uri, IHandler *handler) {
  std::map<std::string, IHandler *>::const_iterator iter = mux_.find(uri);
  assert(iter == mux_.end());
  mux_[uri] = handler;    //??
}

int Server::ListenAndServe(int port, int nthreads, int backlog,
                           IHandler *handler) {
  default_handler_ = handler;    //set default handler
  int r, i;
  int nfd = ensure_listen(port, backlog);
  assert(nfd > 0);
  if (nfd < 0) return -1;
  pthread_t ths[nthreads];
  for (i = 0; i < nthreads; i++) {
    struct event_base *base = event_init();  //begin
    assert(base != NULL);
    struct evhttp *httpd = evhttp_new(base);
    assert(httpd != NULL);
    r = evhttp_accept_socket(httpd, nfd);
    assert(r == 0);
    evhttp_set_gencb(httpd, Server::event_cb, this);
    r = pthread_create(&ths[i], NULL, Server::event_dispatch, base);
    assert(r == 0);
  }
  for (i = 0; i < nthreads; i++) {
    pthread_join(ths[i], NULL);        // wait for pthreads
  }
  return 0;
}

int Server::ensure_listen(int port, int backlog) {  //make socket
  int r;
  int nfd;
  nfd = socket(AF_INET, SOCK_STREAM, 0);
  if (nfd < 0) return -1;

  int one = 1;
  r = setsockopt(nfd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));
  //套接字选项  地址可复用
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  r = bind(nfd, (struct sockaddr *)&addr, sizeof(addr));
  if (r < 0) return -1;
  r = listen(nfd, backlog);
  if (r < 0) return -1;

  int flags;
  if ((flags = fcntl(nfd, F_GETFL, 0)) < 0 ||
      fcntl(nfd, F_SETFL, flags | O_NONBLOCK) < 0)
    return -1;

  return nfd;
}

void Server::event_cb(struct evhttp_request *req, void *arg) {
  Server *server = (Server *)arg;
  std::string uri = evhttp_request_get_uri(req);
  std::map<std::string, IHandler *>::const_iterator iter =
      server->mux_.find(uri);
  if (iter != server->mux_.end()) {
    iter->second->handle(req);
    return;
  }

  if (server->default_handler_ != NULL) {
    server->default_handler_->handle(req);
  }
}

void *Server::event_dispatch(void *arg) {
  event_base_dispatch((struct event_base *)arg);//event_
  return NULL;
}
}