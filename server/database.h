

#ifndef DATABASE_H
#define DATABASE_H

/******mysql*********/
 
#include <string>
#include <iostream>
#include <string.h>  
#include "mysql/mysql.h"
#include <map>
 
using std::string;
typedef  std::map<string,string> result;
typedef  std::map<string,string> item;
/*****************interface*****************/
namespace k
{ 
  class database 
{
public:                    
    virtual int      connect(item* acc)=0;
    virtual result   insert(item* service)=0; 
    virtual result   find(item* service)=0;   
    virtual result   del(item* ID)=0;   
    virtual result   update(item*ID)=0;   
}; 
 
/*******************************************/
 
 class mysql : public database
{    
public:       
    virtual int      connect(item* acc);
    virtual result   insert(item* service); 
    virtual result   find(item* ser_name);   
    virtual result   del(item* ID);   
    virtual result   update(item*ID);  
            result   del_invalid(item *tm);
   void           create_database();      
private:
   int connect_state;
   MYSQL        Mysql;
   MYSQL_RES    *res;
   MYSQL_ROW     row; 
};

 
}
#endif