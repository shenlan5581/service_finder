




#include "database.h"
#include "main.h"
using namespace std;
namespace k
{
  
  database::database()
  {
   
       mysql_init(&mysql);
     if(!mysql_real_connect(&mysql,"localhost","root","xingke",NULL,0,NULL,0))
         cout << "mysql  connect err"<<endl;
      else 
         cout<< "mysql connected"<<endl;
       init_table();
  } 
 
 int database::init_table()
 {     

 
   if(mysql_query(&mysql,SQL_CREATE_DATABASE)==0) 
    { 
         cout<<"create new database"<<endl;
         mysql_query(&mysql,SQL_CHANG_DATABASE);
       
         if(mysql_query(&mysql,SQL_CREATE_TABLE)==0)
         cout<<"create new table"<<endl;
    }
    else 
        mysql_query(&mysql,SQL_CHANG_DATABASE);

 
 

     /* result = mysql_store_result(&mysql);
       while((row = mysql_fetch_row(result)))
     {
       cout <<row[0]<<row[1];
     } 

    }*/
   #undef sql
   return 0;
 }
}