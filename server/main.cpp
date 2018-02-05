

#include "database.h"
 
int main()  
{  
 
 k::mysql  sql("192.168.1.100","root","xingke","service_finder","service_table") ;
       //sql.create_database();  //临时的建库建表操作
 
 /*test*/

      if(!sql.connect())
      
       sql.insert("ftp","192.168.1.1","80");     //ok
       sql.find("ftp");                          //ok
       sql.del("1");                             //ok
       sql.insert("web","192.168.1.2","8080");   //ok
       sql.update("1");                          //ok
      
      
}    