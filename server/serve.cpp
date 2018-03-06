#include <string>
#include <iostream>
#include "log.h"
#include "serve.h"
#include "config.h"
#include "regex"
namespace k {
using namespace std;  

void Serve::handle(struct evhttp_request *req) {
 Json::Value  root ;
 string url = evhttp_request_get_uri(req);  

 regex reg("operate=([a-z]+)&[a-z|\_|0-9]+=[a-z|0-9]+");
 sregex_iterator it(url.begin(),url.end(),reg);
 sregex_iterator end;
if(it != end) {
  string operate = it->str(1);

 if(operate=="register")
   root = Register(&url);
else if(operate=="unregister")
	 root =	UnRegister(&url);
else if(operate=="query")
   root = Query(&url);
else if(operate=="update")
   root = Update(&url);
else {
   root["message"]="operate error";
   log_debug("operate error%s",url);
 }
}
else {
   root["message"]="invalid uri";
   log_warn("invalid uri");
   }
   struct evbuffer *buf;
   buf = evbuffer_new();
	 Json::FastWriter writer;
	 std::string output = writer.write(root);
	 evbuffer_add_printf(buf, output.c_str());
   evhttp_send_reply(req, HTTP_OK, "OK", buf);
   evbuffer_free(buf);  
}

Json::Value Serve::Register(string* url) {
  log_debug("%s",url->c_str());
  Json::Value  root ;
  Mysql sql;
  Pugi conf;
//  url
  regex reg("service_name=([a-z]+)&ip=([0-9]+)&port=([0-9]+)");
  sregex_iterator it(url->begin(),url->end(),reg);
  sregex_iterator end;
if(it != end) {
  string table_name = conf.GetValue("table_name");
  string s_name = it->str(1);
  string s_ip   = it->str(2);
  string s_port = it->str(3);
//  sql
sql.Init(conf.GetValue("MysqlIP"),conf.GetValue("Mysqlusr"),conf.GetValue("Mysqlpassword"), conf.GetValue("Mysqldatabase"));   
string ins ="insert into "+table_name+" (service_name,IP,port)select '"+s_name+"','"+s_ip+"','"+s_port+"' from dual where not exists(select * from "+table_name+" where service_name = '"+s_name+"'and IP = '"+s_ip+"'and port = '"+s_port+"');";
sql.Query(&ins);
string sel ="select * from "+table_name+" where service_name = '"+s_name+"'and IP = '"+s_ip+"'and port = '"+s_port+"';";
result rt = sql.Query(&sel);
//  result
if(rt==nullptr){     //return NULL  mysql connect failed
root["message"] ="failed";
log_error("insert failed mysql connect failed return NULL%s",ins);
} else {  //return NULL
ret::iterator p;
ret  r;
r=(*rt)[0];
p =r.find("state"); 
 if(p->second == "success") { //success 
   r =(*rt)[1];
   root["message"]="success";
   root["ret"]=1;
   root["servers"][0]["id"]=(p=r.find("ID"))->second;
   root["servers"][0]["service_name"] = "-1";
   root["servers"][0]["ip"] = "-1";
   root["servers"][0]["port"] = "-1";
  } else {   
   root["message"]="failed";
  }
}         //return NULL
} else {  // uri invalid 
root["message"]="invalid";
} 
return root;
}

Json::Value Serve::UnRegister(string* url) {
  log_debug("%s",url->c_str());
  Json::Value  root ;
  Mysql sql;
  Pugi conf;
//  url
  regex reg("id=([a-z|0-9]+)");
  sregex_iterator it(url->begin(),url->end(),reg);
  sregex_iterator end;
if(it != end) {
  string table_name = conf.GetValue("table_name");
  string s_id = it->str(1);
//  sql
sql.Init(conf.GetValue("MysqlIP"),conf.GetValue("Mysqlusr"),conf.GetValue("Mysqlpassword"), conf.GetValue("Mysqldatabase"));   
string sel ="delete from "+table_name+" where ID = '"+s_id+"';";
result rt = sql.Query(&sel);
//  result
if(rt==nullptr){     //return NULL  mysql connect failed
root["message"] ="failed";
log_error("delete failed  return NULL%s",sel);
} else {  //return NULL
ret::iterator p;
ret  r;
r=(*rt)[0];
p =r.find("state"); 
 if(p->second == "success") { //success 
   root["message"]="success";
   root["ret"]=1;
   root["servers"][0]["id"]=s_id;
   root["servers"][0]["service_name"] = "-1";
   root["servers"][0]["ip"] = "-1";
   root["servers"][0]["port"] = "-1";
  } else {   
   root["message"]="failed";
  }
}         //return NULL
} else {  // uri invalid 
root["message"]="invalid";
} 
return root;
}

Json::Value Serve::Query(string* url) {
  log_debug("%s",url->c_str());
  Json::Value  root ;
  Mysql sql;
  Pugi conf;
//  url
  regex reg("service_name=([a-z]+)");
  sregex_iterator it(url->begin(),url->end(),reg);
  sregex_iterator end;
if(it != end) {
  string table_name = conf.GetValue("table_name");
  string s_name = it->str(1);
  string query_time = conf.GetValue("query_time");
//  sql
sql.Init(conf.GetValue("MysqlIP"),conf.GetValue("Mysqlusr"),conf.GetValue("Mysqlpassword"), conf.GetValue("Mysqldatabase"));   
string sel ="select * from "+table_name+" where service_name = '"+s_name+"'"+" and  UNIX_TIMESTAMP(time)>UNIX_TIMESTAMP(now())-"+query_time+";";
result rt = sql.Query(&sel);
//  result
if(rt==nullptr){     //return NULL  mysql connect failed
root["message"] ="failed";
log_error("query failed  return NULL%s",sel);
} else {  //return NULL
ret::iterator p;
ret  r; 
r=(*rt)[0];
p =r.find("state");   
 if(p->second == "success") { //success 
   root["message"]="success";
   root["ret"]=(*rt).size()-1;
for(int i=1;i<(*rt).size();i++) {
   root["servers"][i-1]["id"]=            (p =(*rt)[i].find("ID"))->second;
   root["servers"][i-1]["service_name"] = (p =(*rt)[i].find("service_name"))->second;
   root["servers"][i-1]["ip"] =           (p =(*rt)[i].find("IP"))->second;
   root["servers"][i-1]["port"] =         (p =(*rt)[i].find("port"))->second;
   }
  } else {       //mysql api function error
   root["message"]="failed";
  }
}         //return NULL
} else {  // uri invalid 
root["message"]="invalid";
} 
return root;
}

Json::Value Serve::Update(string* url) {
  log_debug("%s",url->c_str());
  Json::Value  root ;
  Mysql sql;
  Pugi conf;
//  url
  regex reg("id=([0-9]+)");
  sregex_iterator it(url->begin(),url->end(),reg);
  sregex_iterator end;
if(it != end) {
  string table_name = conf.GetValue("table_name");
  string s_id = it->str(1);
//  sql
sql.Init(conf.GetValue("MysqlIP"),conf.GetValue("Mysqlusr"),conf.GetValue("Mysqlpassword"), conf.GetValue("Mysqldatabase"));   
string sel = "update "+table_name+" set time = now() where ID = "+s_id+";";
cout<<sel<<endl;
result rt = sql.Query(&sel);
//  result
if(rt==nullptr){     //return NULL  mysql connect failed
root["message"] ="failed";
log_error("query failed  return NULL%s",sel);
} else {  //return NULL
ret::iterator p;
ret  r; 
r=(*rt)[0];
p =r.find("state");   
 if(p->second == "success") { //success 
   root["message"]="success";
  } else {       //mysql api function error
   root["message"]="failed";
  }
}         //return NULL
} else {  // uri invalid 
root["message"]="invalid";
} 
return root;
}

void Serve::Clear(void) {  //delete invalide service if time out
while(1) {
  cout<<"clear"<<endl;
  Mysql sql;
  Pugi conf;
  string query_time = conf.GetValue("query_time");
  string table_name = conf.GetValue("table_name");
//  sql
  sql.Init(conf.GetValue("MysqlIP"),conf.GetValue("Mysqlusr"),conf.GetValue("Mysqlpassword"), conf.GetValue("Mysqldatabase"));   
string sel ="delete from "+table_name+" where UNIX_TIMESTAMP(time)<UNIX_TIMESTAMP(now())-"+query_time+";";  
result rt = sql.Query(&sel);
if(rt==nullptr)     //return NULL  mysql connect failed
log_error("query failed  return NULL%s",sel);

sleep(atoi((conf.GetValue("time_out")).c_str()));
}
}
}  //namespace



