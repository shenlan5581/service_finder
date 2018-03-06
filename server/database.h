/*
  返回参数为 unique_ptr<vector<map<string,string>>
  如果为nullptr则链接失败  
  vector 的第一个元素的“state"为状态信息
   vector的其他元素为查询数据
  vector[0].find("state");
 
 error
1链接失败                                                                return nullptr
2查询失败 可能 查询语句错误（是否可控）          stata = failed
3查询为空                                                                state =success 
*/ 
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iostream>
#include <string.h>  
#include <mysql.h>
#include <map>
#include <vector>
#include <memory> 
using namespace std;
 
namespace k
{ 
typedef map<string,string> ret;    //element
typedef vector<ret>        rets;   //return
typedef unique_ptr<rets>   result;

class DataBase {
 public:
  virtual result Query(string *req)=0; 
};

class Mysql : public DataBase {
 public:
	virtual result Query(string *req) override;
 	void Init(string IP,string usr,string password,string database);
 private:
  MYSQL mysql;
  vector<string> config;
}; 
}//namespace
#endif
