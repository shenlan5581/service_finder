
 
#include "database.h"
 
using namespace std;
namespace k
{   
 database::database(string addr,string user,string password,string database_name,string table_name)
 {  
    m_addr=addr;
    m_user =user;
    m_password = password; 
    m_database_name = database_name;
    m_table_name = table_name;
 }

mysql::mysql(string addr,string user,string password,string database_name,string table_name): database(addr,user,password,database_name,table_name) 
{     
}   
int   mysql::connect()
{     
       mysql_init(&Mysql); 
   if(!mysql_real_connect(&Mysql,m_addr.c_str(),m_user.c_str(),m_password.c_str(),m_database_name.c_str(),0,NULL,0))
        {  
          cout << "mysql connect err"<<endl;  
          connect_state = 0;
          return -1;         
        }   
      else 
        {         
           cout << "mysql connected"<<endl; 
           connect_state = 1;
           return 0; 
        }    
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
     mysql_real_connect(&Mysql,m_addr.c_str(),m_user.c_str(),m_password.c_str(),NULL,0,NULL,0);
     mysql_query(&Mysql,SQL_CREATE_DATABASE);
     mysql_query(&Mysql,SQL_CHANG_DATABASE); 
     mysql_query(&Mysql,SQL_CREATE_TABLE); 

 #endif
 }


 
 JSON  mysql::insert(string service_name,string ip,string port)
{     
     if(!connect_state)
     return   0 ;
      string sql =   "insert into "+m_table_name+" (service_name,IP,port ) values ('"+service_name+"','"+ip+"','"+port+"');";
      string sql2 =  "select * from "+m_table_name+" where service_name = '"+service_name+"' and ip = '"+ip+"' and port = '"+port+"';";
 
      cout<<sql2<<endl;
     if(!mysql_query(&Mysql,sql2.c_str()))  // =0成功  
      {
          result = mysql_store_result(&Mysql);      //获取结果集合
          int row_count = mysql_num_rows(result);   // 结果数目
              cout << row_count;                    // #####
            if(row_count == 0)  //无此记录 插入
            { 
              cout<<sql<<endl;
             if(!mysql_query(&Mysql,sql.c_str()))  
               cout <<"insert successd";

             }
            else  //记录已经存在   
            {  
              cout<<"exiset";
            }
      }       
      else    //函数错误  
      {            
        cout<<"err";            
      }             
    mysql_free_result(result);
 
} 
 
 JSON mysql::find(string service_name)
{ 
    if(!connect_state)
     return   0 ;
  string sql2 =  "select * from "+m_table_name+" where service_name = '"+service_name+"';";


          cout<<sql2<<endl;
       if(!mysql_query(&Mysql,sql2.c_str()))  //       =0成功  
         {
              result = mysql_store_result(&Mysql);      //获取结果集合      A


          int row_count = mysql_num_rows(result);       // 结果数目         B
              cout <<"rows:"<< row_count<<endl ;        //test
            if(row_count != 0)      //查到记录
          {  
   
              /* MYSQL_FIELD* field=NULL;                //输出字段名        C
               for(int i = 0;i<mysql_num_fields(result);i++)
               {
                   field = mysql_fetch_field_direct(result,i);//获取 每个字段名   
                   cout<<field->name;
               }*/

                while(row =mysql_fetch_row(result))       //抓取一行         D
             {  
                   for(int t =0;t<mysql_num_fields(result);t++)    
                      { 
                          cout << row[t]<<" " ;           // 输出值          E  
                      } 
             }
                //mysql_num_fields(result) 获取每行字段个数
 
                //return json
             }
            else    //记录不存在
            {  
              cout<<"non-existent";
            }
      }       
      else    //函数错误  
      {            
        cout<<"err";      
        //返回   
      }  
  mysql_free_result(result);
}
 
JSON  mysql::del(ID id)    
 {
 if(!connect_state)
     return   0 ;
       
   string sql =   "delete from "+m_table_name+" where ID= "+id+";";
   string sql2 =  "select ID from "+m_table_name+" where ID ="+id+";";
 
      cout<<sql2<<endl; 
       if(!mysql_query(&Mysql,sql2.c_str()))             // =0成功  
      {  
           result = mysql_store_result(&Mysql);          //获取结果集合  A
          int row_count = mysql_num_rows(result);        // 结果数目   B
              cout <<"rows:"<< row_count<<endl ;         //test
            if(row_count != 0)                           //查到记录
          {  
             if(!mysql_query(&Mysql,sql.c_str()))        //删除
                 cout <<"delete successd"<<endl;
          }    
          else   
            {  
              cout<<"non-existent";
            }  
      }       
      else    //函数错误  
      {            
        cout<<"err";      
        //返回   
      }             
 mysql_free_result(result);
 }
JSON   mysql::update(ID id)
{
   if(!connect_state)
     return   0 ;

   string sql  =   "update "+m_table_name+" set time = now() where ID = "+id+";";
   string sql2 =   "select ID from "+m_table_name+" where ID ="+id+";";
 
      cout<<sql2<<endl;
       if(!mysql_query(&Mysql,sql2.c_str()))  // =0成功  
      {
           result = mysql_store_result(&Mysql);         // 获取结果集合  A
          int row_count = mysql_num_rows(result);       // 结果数目   B
              cout <<"rows:"<< row_count<<endl ;        //test
            if(row_count != 0)      //查到记录
          {  
             if(!mysql_query(&Mysql,sql.c_str()))        //update
                 cout <<"update successd"<<endl;

          }    
          else   
            {  
              cout<<"non-existent";
            }  
      }       
      else    //函数错误  
      {            
        cout<<"err";      
        //返回   
      }             
 mysql_free_result(result);
 
}
 mysql::~mysql() 
 {
    mysql_close(&Mysql);
    mysql_library_end();
 }
  
 
}