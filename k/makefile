ifeq ($(make_basedir), ) 
	make_basedir := 
endif

CXXFLAGS := -g -std=c++11
 
INCLUDE := -I$(make_basedir) lib
INCLUDE += -I$(make_basedir) include
INCLUDE += -I$(make_basedir) lib/libevent/include
INCLUDE += -I$(make_basedir) lib/mysql/include


LIBDIR := -L. 
LIBDIR += -L$(make_basedir) lib
LIBDIR += -L$(make_basedir) lib/libevent/lib 
LIBDIR += -L$(make_basedir) lib/mysql/lib 
LIBDIR += -L/usr/lib64 

LIB := -levent -lpthread -lmysqlclient  #-ljsoncpp  #-lmysqlpp 

.cpp.o:
	g++ $(CXXFLAGS) $(INCLUDE) -Wno-deprecated -c -o $@ $< 

.c.o:
	gcc $(CXXFLAGS) -c -o $@ $<   
 
 
src := main.cpp
src += http_server.cpp
src += serve.cpp
src += database.cpp
src += msg.cpp
 
obj := $(src:.cpp=.o)

run:all
	./main

all : $(obj)   
	g++ -o main $(INCLUDE) $(obj) $(LIBDIR) $(LIB) -Wl,-rpath,../lib -Wl,-rpath,../../lib,-rpath,./ -fPIC
 
clean: $(obj)
	rm -f *.o
	rm -f main
