
#pragma once
#include <string>
namespace k {
using std::string;
typedef string JSON;
class HttpClient {
 public:	
 virtual JSON Get(string url) = 0;
 virtual JSON post(string url,string data) = 0;
};
class Curl : public HttpClient {
 public:
          Curl();
         ~Curl();
  virtual JSON Get(string url);
  virtual JSON post(string url,string data){} ;
  static size_t write_data_cb(void * buffer,size_t,size_t nmemb,void *userp);
 private:
  JSON result;
};
} //namespace end

