

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iostream>
#include "mysql/mysql.h"


namespace k
{
  class database
{
public:
    int status;
    database();
     
    int insert();
    int find();  
    int del();
public:
    int  init_table();
   
   MYSQL        mysql;
   MYSQL_RES   *result;
   MYSQL_ROW    row;
 
};
 

}
#endif