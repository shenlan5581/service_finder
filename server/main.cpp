

#include "database.h"
 
typedef  std::map<string,string> result;
typedef  std::map<string,string> item;

int main()  
{  

       item i;
       k::mysql  sql;
       i["addr"]="192.168.1.101";
       i["user"]="root";
       i["password"]= "xingke";
       i["database_name"]="service_finder";

     if(sql.connect(&i)==0)
      {    
        return 0; 
      }

sql.create_database();
       i.clear();
       i["table_name"]="service_table";
       i["service_name"]="dns";
       i["ip"]= "192.168.1.121";
       i["port"]="21";
       sql.insert(&i);  //ok
   
 
      i.clear();
       i["service_name"]="dns";
       i["table_name"]="service_table";
       i["time"]="40";
       sql.find(&i);  
                                 //ok
       i.clear();
       i["time"]="20";
       sql.del_invalid(&i);     //ok                          
      
       i.clear();
       i["table_name"]= "service_table"; 
       i["id"]="10"; 
       sql.update(&i);   //ok   
       
        i.clear();
       i["table_name"]= "service_table"; 
       i["id"]="10"; 
       sql.del(&i);
                        
}    