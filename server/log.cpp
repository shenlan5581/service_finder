#include "log.h"
namespace k {
Log log;
time_t tm;
int Log::begin(){
filefd = fopen(SAVEFILENAME,"a");
if(filefd == NULL)
return 0;
else
return 1;
} 
char * Log::getdate(){
time(&tm);
return ctime(&tm);
}
}

	
