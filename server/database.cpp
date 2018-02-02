




#include "database.h"
#include "main.h"
using namespace std;
namespace k
{
  database::database()
  {
       mysql_init(&mysql);
     if(!mysql_real_connect(&mysql,"localhost","root","xingke",NULL,0,NULL,0))
        {  status =-1;
           cout << "mysql  connect err"<<endl;
        }
      else 
      {
         status =1;
         cout<< "mysql connected"<<endl;
         init_table();
      }
  } 
 
 int database::init_table()
 {     
         mysql_query(&mysql,SQL_CREATE_DATABASE);
         mysql_query(&mysql,SQL_CHANG_DATABASE); 
         mysql_query(&mysql,SQL_CREATE_TABLE);
     /* result = mysql_store_result(&mysql);
       while((row = mysql_fetch_row(result)))
     {
       cout <<row[0]<<row[1];
     } 

    }*/
   return 0;
 }






}