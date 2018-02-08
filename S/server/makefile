ifeq ($(make_basedir),) 
	make_basedir := ..
endif

CXXFLAGS := -g -std=c++11

INCLUDE := -I$(make_basedir)/# -I ../ -I ../deps  在文件夹中寻找头文件 
INCLUDE += -I$(make_basedir)/deps
INCLUDE += -I$(make_basedir)/deps/libevent/include
INCLUDE += -I$(make_basedir)/deps/jsoncpp/include
INCLUDE += -I$(make_basedir)/deps/mysql++/include
INCLUDE += -I/usr/include/mysql

LIBDIR := -L.# -I ../ -I ../deps  在文件夹中寻找库文件
LIBDIR += -L$(make_basedir)/deps
LIBDIR += -L$(make_basedir)/deps/libevent/lib 
LIBDIR += -L$(make_basedir)/deps/jsoncpp/lib
LIBDIR += -L$(make_basedir)/deps/mysql++/lib
LIBDIR += -L/usr/lib64 

LIB := -levent -lpthread -ljsoncpp -lmysqlclient #-lmysqlpp 

.cpp.o:
	g++ $(CXXFLAGS) $(INCLUDE) -Wno-deprecated -c -o $@ $< 

.c.o:
	gcc $(CXXFLAGS) -c -o $@ $<   
 
 
src := main.cpp
src += http_server.cpp
 
obj := $(src:.cpp=.o)

all : $(obj)   #main.o http_server.o
	g++ -o main $(INCLUDE) $(obj) $(LIBDIR) $(LIB) -Wl,-rpath,../lib -Wl,-rpath,../../lib,-rpath,./ -fPIC
# g++ -o main -I ./ main.o http_server.o
clean: $(obj)
	rm -f *.o
	rm -f main
