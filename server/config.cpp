


#include "config.h"

namespace k{

Config * Global_config = Config::GetInstance();
Config * Config::config_ = NULL;

Config::Config()
{
   configure_ = new Pugi; 		 
}
Config::~Config()
{
  delete config_;
  delete configure_;
}
Config * Config::GetInstance() {
    if (config_  == NULL)
      { 
 	  config_ = new Config;         
             int err =0;
      err = config_->init() ;
	return config_;
      } else {
	return config_;
      }
}
int Config::init()
{
 conf_info.addr = configure_->GetValue("ip");

 conf_info.user = configure_->GetValue("user");
 
 conf_info.password = configure_->GetValue("password");
 
 conf_info.database_name = configure_->GetValue("database_name");
 
 conf_info.time_out  = configure_->GetValue("time_out");
 
 conf_info.last_time = configure_->GetValue("last_update_time");
 conf_info.log_flush_time = configure_->GetValue("log_flush_time");
}




string Config::GetValue(string name) {
  return (configure_->GetValue( name ));
}
int Pugi::init()
{
  result_  =  doc_.load_file(CONFIG_PATH);
  if(!result_)
  cout<<"xml init failed"<<endl;
}
string Pugi::GetValue(string name) {
if(!result_)
    init();
  const pugi::char_t *find =name.c_str();
  pugi::xml_node node;
  node = doc_.first_child();
  node = node.child(find);
  node = node.first_child();
  const pugi::char_t *o = node.value();
  string value = o ;
  return value;

}
/****xml*****
//节点 值
 pugi::xml_node n;
 cout<<result_.description()<<endl;
   n = doc_.first_child();          //跟节点 
   n = n.first_child();             //info节点
 const pugi::char_t* k = n.name();  //第一个节点的 名称
   n = n.first_child();
 const pugi::char_t* v = n.value(); //文本几点的值
  cout<<k<<endl;
  cout<<v<<endl;

//获取属性
 pugi::xml_node s;
 s = doc_.first_child();
 s = s.first_child();
 pugi::xml_attribute a = s.first_attribute();
 const pugi::char_t* ar  = a.value(); 
//查找
  pugi::xml_node g;
  g= doc_.first_child();
  g = g.first_child();
  g = g.first_child();
  const pugi::char_t *o = g.value();
  cout<<"dd"<<o<<"dd"<<endl;  
  cout<<ar<<endl;
  cout<<name<<endl;
*/










}//namespace k end
