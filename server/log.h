/*
   c文件中声明了全局变量 log 
   use like this:
   extern ServeLog log; 

   LogInfo * info = new ServeLogInfo;
   info->MakeInfo( ... ...);    
   log,AddLog(info); 
            
*/
#ifndef LOG_H
#define LOG_H
#include <pthread.h>
#include <time.h>
#include <queue>
using namespace std;
namespace k{

class LogInfo {
 public:
  virtual int FlushToFile()=0;
}; 
class ServeLogInfo : public LogInfo {
 public:
int	MakeInfo(int lineNo,string save_file_name,string file_name,string description);
  virtual int  FlushToFile();
 private:
	int lineNo_;
	string save_file_name_;
	string file_name_;
	string description_;
};



class Log {
 public:
    virtual int AddLog(LogInfo *)=0;
    virtual bool Start()=0; 
    virtual bool Stop()=0; 
};

class ServeLog : public Log {
 public:
    virtual int  AddLog(LogInfo *);
    virtual bool Start(); 
    virtual bool Stop(); 
 private:
	  queue<LogInfo *> queue_;
    pthread_t        pid_;
static  void * Flush(void *);
    
};  
}//  namespace k end
#endif
