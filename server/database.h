

#ifndef DATABASE_H
#define DATABASE_H

/******mysql*********/
 
#include <string>
#include <iostream>
#include <string.h>  
#include "mysql/mysql.h"
#include "macro.h" 
#include <map>
 
using std::string;
/*****************interface*****************/
namespace k
{ 
  class database 
{

  std::map<string,string> patameter;
public:  
                   database(string addr,string user,string password,string database_name,string table_name); 
    virtual int    connect()=0;
    virtual JSON   insert(string service_name,string ip,string port)=0; 
    virtual JSON   find(string service_name)=0;   
    virtual JSON   del(ID)=0;   
    virtual JSON   update(ID)=0;   
    string m_addr;
    string m_user;
    string m_password;
    string m_database_name;
    string m_table_name;

    int connect_state;
}; 
 
/*******************************************/
 




/*ID 用数据库AUTO_INCREMENT  应该够用了*/
 class mysql : public database
{    
public:
                  mysql(string addr,string user,string password,string database_name,string table_name);
  
   virtual int    connect();
   virtual JSON   insert(string service_name,string ip,string port); 
   virtual JSON   find(string service_name);   
   virtual JSON   del(ID);    
   virtual JSON   update(ID);  

   void           create_database();    

                  ~mysql();
private:
   MYSQL        Mysql;
   MYSQL_RES   *result;
   MYSQL_ROW    row; 
};

 
}
#endif