/*
* pugixml
*
*/

#pragma once
#include<string>
#include<iostream>
#include<pugiconfig.hpp>
#include<pugixml.hpp>
using std::string;
namespace k {
#define CONFIG_PATH "./config.xml"

class Config {
 public:
  virtual	string GetValue(string item)=0;
};  

class Pugi : public Config {
 public:
  virtual string GetValue(string item); 	
 private:
  pugi::xml_document doc;
  pugi::xml_parse_result result;
};

}// namespace 
