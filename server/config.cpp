#include "config.h"
#include "log.h"
namespace k {
using namespace std;
string Pugi::GetValue(string name) {
  result  =  doc.load_file(CONFIG_PATH);
  if(!result) {
  log_error("pugi init failed");
  cout<<"xml init failed"<<endl;
  return nullptr;
} else {
  const pugi::char_t *find =name.c_str();
  pugi::xml_node node;
  node = doc.first_child();
  node = node.child(find);
  node = node.first_child();
  const pugi::char_t *o = node.value();
  string value = o ;
  return value;
 }
}

} //namespace
