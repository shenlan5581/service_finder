#include "database.h"
#include "log.h"
namespace k {
result Mysql::Query(string *req) {
result rt(new rets);
mysql_init(&mysql);
if(!mysql_real_connect(&mysql,config[0].c_str(),config[1].c_str(),config[2].c_str(),config[3].c_str(),0,NULL,0)) {
     log_error("connecting to mysql failed");
     rt.reset();
} else {
auto fun = [&](){ 
ret        item;
MYSQL_RES * res;
MYSQL_ROW   row;
MYSQL_FIELD *fd;
if(mysql_query(&mysql,req->c_str())) { 
     log_debug("query faild");
     item["state"] = "failed"; 
     rt->push_back(item);
 } else {
      item["state"] = "success"; 
      rt->push_back(item);
      res = mysql_store_result(&mysql);
    if(res != nullptr) {  
      item.clear(); 
      vector<string> key;  //save key
      while(fd = mysql_fetch_field(res)) {
           key.push_back(fd->name);  
          } 
      while((row = mysql_fetch_row(res))) {
          for(int i=0;i<key.size();i++) {
           item[key[i]] = row[i]; 
  //test  cout<<key[i]<<row[i]<<endl; 
           } 
           rt->push_back(item);
 					 item.clear();  
       }
      mysql_free_result(res);
     } 
   }
 };
fun();
}
mysql_close(&mysql);
return rt;
}
void Mysql::Init(string IP,string usr,string password,string database) {
config.push_back(IP);
config.push_back(usr);
config.push_back(password);
config.push_back(database);
}

} //namespace


