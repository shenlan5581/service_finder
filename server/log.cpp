
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "log.h"
#include "config.h"

using namespace std;
namespace k {

ServeLog log;

extern Config * Global_config;
pthread_mutex_t info_queue;

int ServeLogInfo::MakeInfo(int lineNo,string save_file_name,string file_name,string description) {
  if (lineNo < 0) 
  	return -1;
 lineNo_ = lineNo;
	if (save_file_name.empty())
    return -1;
 save_file_name_ = save_file_name;
  if (file_name.empty())
    return -1;
  file_name_ = file_name;
  if (description.empty())
		return -1;
  description_ = description;
return 0;
}
int ServeLogInfo::FlushToFile() {
   ofstream fout;
   time_t tm;
   time(&tm); 
   fout.open(save_file_name_,ios::app);
    if(fout.fail())
    return -1;
		fout<<to_string(lineNo_)<<" "<<file_name_<<"  "<<description_<<"  "<<ctime(&tm); 
   fout.close();
return 0;
}

int ServeLog::AddLog(LogInfo * node) {
 
 pthread_mutex_lock(&info_queue);
  queue_.push(node);
 pthread_mutex_unlock(&info_queue);
return 1;
}
bool ServeLog::Start() {
   int err;
 pthread_mutex_init(&info_queue,NULL);
 err = pthread_create(&pid_,NULL,Flush,&queue_);
   if (err == 0)
      return true;
   else
      return false; 
}
bool ServeLog::Stop() {
   pthread_cancel(pid_);
   return true;
}

void *ServeLog::Flush(void * para) {
 queue<LogInfo *> * Queue; 
 Queue = (queue<LogInfo *>*)para;
 LogInfo * info;
 int time =atoi((Global_config->conf_info.log_flush_time).c_str());
while(1)
{ 
 pthread_mutex_lock(&info_queue);
   while (!Queue->empty())
  {
    info = Queue->front();
    info->FlushToFile();
    Queue->pop();
    delete info;
  }
   pthread_mutex_unlock(&info_queue);
 sleep(time);
}
}


} //namespace k end
