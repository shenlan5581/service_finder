
 
#include "database.h"
 
using namespace std;
namespace k
{   
#define  E(C)     (((iter = MARAMETER->find(C))->second).c_str())    // get key_value of map
#define  S(C)     (((iter = MARAMETER->find(C))->second))            // get key_value of map
#define  UNCONNECTED      if(!connect_state){ ret["state"] = "error" ;return ret ;}  
#define  T(X) std::cout<<X;

int   mysql::connect(item *acc)
{     
 item::iterator iter; 
 #define  MARAMETER   acc
       mysql_init(&Mysql); 
   if(!mysql_real_connect(&Mysql,E("addr"),E("user"),E("password"),E("database_name"),0,NULL,0))
        {                                       
          connect_state = 0; cout <<"01"<<endl;
      #undef  MARAMETER 
          return 0;          
        }   
      else       //successed           
        {  
           connect_state = 1;     
       #undef  MARAMETER 
           return 1; 
        }    
    
}  

result mysql::insert(item * service)
{       
 item::iterator iter; 
 #define  MARAMETER   service
 result ret;
 UNCONNECTED 
string sql_ins  =   "insert into "+S("table_name")+" (service_name,IP,port ) values ('"+S("service_name")+"','"+S("ip")+"','"+S("port")+"');";
string sql_sel  =   "select * from "+S("table_name")+" where service_name = '"+S("service_name")+"' and ip = '"+S("ip")+"' and port = '"+S("port")+"';";
string sql_ID  =    "select * from "+S("table_name")+" where service_name = '"+S("service_name")+"' and ip = '"+S("ip")+"' and port = '"+S("port")+"';";
    if(!mysql_query(&Mysql,sql_sel.c_str()))  
      {
         res = mysql_store_result(&Mysql);      
          int row_count = mysql_num_rows(res);               
            if(row_count == 0)    
            {   
                 
             if(!mysql_query(&Mysql,sql_ins.c_str()))  
              {
                   if(!mysql_query(&Mysql,sql_sel.c_str())) 
                   {     
                     res = mysql_store_result(&Mysql); 
                        
                        row_count= mysql_num_rows(res);             
                        if(row_count != 0)
                        {  
                          row = mysql_fetch_row(res);    
                          ret["id"]=row[0];                 //E  
                          ret["state"] = "success";
                        }else 
                       {  
                         ret["id"]=-1;  
                       }
                   }
              }

            }  
            else   
            {  
              ret["state"] = "item exiset";
            }
      }       
      else    
      {            
        ret["state"] = "error";
      }   
     mysql_free_result(res);
   #undef  MARAMETER  
  return  ret;
} 
 
 v_result mysql::find(item* ser_name)  //find time <  
{  
 item::iterator iter;   
 v_result rets;
  result ret; 
 #define  MARAMETER   ser_name
 #define  RET_ERROR         ret["state"] = "error";\
                            rets.push_back(ret);\
                           
      if(!connect_state)
       {
       RET_ERROR
       return  rets;
       }
 
  string sql_find = "select * from "+S("table_name")+" where service_name = '"+S("service_name")+"' and  UNIX_TIMESTAMP(time)>UNIX_TIMESTAMP(now())-"+S("time")+";";      
  if(!mysql_query(&Mysql,sql_find.c_str()))    
       {  
          res = mysql_store_result(&Mysql);                     //       A
          int row_count = mysql_num_rows(res);       
            if(row_count != 0)                                  // 
           {  
                 /*  MYSQL_FIELD * field=NULL;                  //       C
                  for(int i = 0;i<mysql_num_fields(res );i++)
                    {
                      // field = mysql_fetch_field_direct(res ,i);// 
                      // cout<<field->name;*/
              ret["state"]="success";
              rets.push_back(ret);
                   while((row = mysql_fetch_row(res )))           //     D
                      {    
                         ret["id"] = row[0];                      //      E  
                         ret["service_name"] = row[1];
                         ret["ip"] = row[2]; 
                         ret["port"] = row[3]; 
                         ret["time"] = row[4];  
                         rets.push_back(ret);
                         ret.clear();
                      }    
           }
            else      
            {  
              ret["state"]="non-existent";
              rets.push_back(ret);
            }
        }        
      else    //函数错误  
      {            
       RET_ERROR 
      }  
  mysql_free_result(res);
  #undef  MARAMETER
  return rets;
}
 
result mysql::del(item * id)    
 {
 item::iterator iter; 
 #define  MARAMETER   id
 result ret; 
 UNCONNECTED 
       
   string sql_del =   "delete from "+S("table_name")+" where ID= "+S("id")+";";
   string sql_sel =  "select ID from "+S("table_name")+" where ID ="+S("id")+";";
  
       if(!mysql_query(&Mysql,sql_sel.c_str()))             
      {  
           res = mysql_store_result(&Mysql);          
          int row_count = mysql_num_rows(res);         
            if(row_count != 0)                            
          {  
             if(!mysql_query(&Mysql,sql_del.c_str()))        
                ret["state"] = "success";
          }    
          else   
            {  
               ret["state"] = "non-existent";
            }  
      }       
       else    
      {            
         ret["state"] = "error";          
      }             
 mysql_free_result(res);
 #undef  MARAMETER
 return ret;
}
result  mysql::update(item *id)
{
  item::iterator iter; 
  #define  MARAMETER   id
  result ret; 
  UNCONNECTED 
 
   string sql_upd  =  "update "+S("table_name")+" set time = now() where ID = "+S("id")+";";
   string sql_sel  =  "select ID from "+S("table_name")+" where ID ="+S("id")+";";
 
       if(!mysql_query(&Mysql,sql_sel.c_str()))  
      {
           res = mysql_store_result(&Mysql);         
          int row_count = mysql_num_rows(res);           
            if(row_count != 0)       
          {  
             if(!mysql_query(&Mysql,sql_upd.c_str()))        //update
                 ret["state"] = "success"; 
                 ret["id"] = S("id");
          }    
          else   
            {  
                ret["state"] ="non-existent"; 
            }  
      }       
      else    //函数错误  
      {            
      ret["state"] ="error";     
        //返回   
      }             
 mysql_free_result(res);
 #undef  MARAMETER
 return ret;
}
 
result mysql::del_invalid(item *tm)
 { 
  item::iterator iter; 
  #define  MARAMETER tm
  result ret;  
  UNCONNECTED 
    string id;                                             
    string sql_sel = "select ID from service_table where UNIX_TIMESTAMP(time)<UNIX_TIMESTAMP(now())-"+S("time")+";";  
                
       if(!mysql_query(&Mysql,sql_sel.c_str()))  
      {
           res = mysql_store_result(&Mysql);         
          int row_count = mysql_num_rows(res);            
            if(row_count != 0)       
          {  
              while((row = mysql_fetch_row(res )))       
                {     
                  id =row[0];
                  string sql_del =  "delete from  service_table where ID="+id+";";  
                  mysql_query(&Mysql,sql_del.c_str()); 
                  cout<<"time out delete "+id<<endl;          
                }  
                ret["state"] ="delete success";  
          }     
          else   
         {  
            ret["state"] ="it's clean";
         }  
      }       
      else    //函数错误  
      {            
      ret["state"] ="error";            
      }
  if(res == NULL)
 cout<<"test"<<endl;     
 mysql_free_result(res);
 
 #undef  MARAMETER
 return ret;
 }  
  void mysql::create_database()     /* 临时的建库操作  */
 { 

  #ifndef  DATABASE_EXISTS
  #define SQL_CREATE_DATABASE "create database  IF NOT EXISTS service_finder;" 
  #define SQL_CHANG_DATABASE  "use service_finder;"     
  #define SQL_CREATE_TABLE    "create table IF NOT EXISTS  service_table(\
                              ID int unsigned not null auto_increment primary key,\
                              service_name char(50) not null, \
                              IP char(20)    not null, \
                              port char(10)  not null, \
                              time timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP\
                              );"     
     mysql_init(&Mysql);
     cout<<"create database and table"<<endl;
     mysql_real_connect(&Mysql,"192.168.1.101","root","xingke",NULL,0,NULL,0);
     mysql_query(&Mysql,SQL_CREATE_DATABASE);
     mysql_query(&Mysql,SQL_CHANG_DATABASE); 
     mysql_query(&Mysql,SQL_CREATE_TABLE); 

 #endif
 }

mysql::~mysql()  
{  
   mysql_close(&Mysql);   
} 
 
}
