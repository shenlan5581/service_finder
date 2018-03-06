#define  LOGLEVEL 4
#include <stdio.h>
#include <functional>
#include <iostream>
#include <thread>
#include <string>
#include  "http_server.h" 
#include  "./lib/json/json/json.h"   
#include  "config.h"
#include  "log.h"
#include  "database.h"
#include  "serve.h"
using namespace std;
using namespace placeholders;
using namespace k;
using namespace std;
int main() {  
cout<<log.getdate()<<endl;
assert(log.begin());
log_info("system start");
http::Server server;
thread t1(Serve::Clear);
server.Handle("/service_finder",new Serve);
   server.ListenAndServe(80,2, 1024, NULL); 
}
