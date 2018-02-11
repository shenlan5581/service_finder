ifeq ($(make_basedir), ) 
	make_basedir := 
endif

CXXFLAGS := -g  -std=c++11
INCLUDE := -I. 
INCLUDE += -I$(make_basedir) lib
INCLUDE += -I$(make_basedir) include
INCLUDE += -I$(make_basedir) lib/libevent/include
INCLUDE += -I$(make_basedir) lib/a/include
 


LIBDIR := -L. 
LIBDIR += -L$(make_basedir) lib
LIBDIR += -L$(make_basedir) lib/libevent/lib 
LIBDIR += -L$(make_basedir) lib/sql/lib 
LIBDIR += -L$(make_basedir) lib/json
 

LIB := -levent -lpthread -lmysqlclient -ljsoncpp   

.cpp.o:
	g++ $(CXXFLAGS) $(INCLUDE) -Wno-deprecated -c -o $@ $< 

 
src := main.cpp
src += http_server.cpp
src += serve.cpp
src += database.cpp
 
obj := $(src:.cpp=.o) 

run:all
	./main

all : $(obj)   
	g++  -g -o  main $(INCLUDE) $(obj) $(LIBDIR) $(LIB) -Wl,-rpath ./lib/sql/lib -fPIC
 
clean: $(obj)
	rm -f *.o
	rm -f main
