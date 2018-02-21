/*
*  配置类
*
*
*/
																												
#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <string>
#include <iostream>

#include <pugiconfig.hpp>
#include <pugixml.hpp>

#include "config.h"

namespace k{

#define CONFIG_PATH  "./config.xml"

class Configure;

using namespace std;

struct Conf_Info{
 //mysql
	string addr;
  string port;
  string user;
	string password; 
  string database_name;
  string log_flush_time; 
	//option
 	string time_out;    // time out for delete
  string last_time;   // time for find near to last update
};

class Config {

public:
 static  Config*   GetInstance();
         string    GetValue(string name);
        ~Config();
public:
         Conf_Info     conf_info;
private:
         Config();
   int   init(); 
static   Config *      config_;                 
         Configure *   configure_;
};  


class Configure { 
 public:
   virtual string  GetValue(string name)=0;
};


class Pugi : public Configure {
 public:
    	Pugi(){};
	   ~Pugi(){}; 
   virtual string  GetValue(string name);
 private:
   int init();
   pugi::xml_document doc_;
	 pugi::xml_parse_result result_; 
};





} //namespace k end
#endif

