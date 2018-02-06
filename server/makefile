ifeq ($(make_basedir),) 
	make_basedir := ..
endif

CXXFLAGS := -g -std=c++11

INCLUDE := -I$(make_basedir)/
INCLUDE += -I$(make_basedir)/deps
INCLUDE += -I$(make_basedir)/deps/libevent/include
INCLUDE += -I$(make_basedir)/deps/jsoncpp/include

LIBDIR := -L$(make_basedir)/deps
LIBDIR += -L$(make_basedir)/deps/libevent/lib 
LIBDIR += -L$(make_basedir)/deps/jsoncpp/lib

LIB := -levent -lpthread -ljsoncpp

.cpp.o:
	g++ $(CXXFLAGS) $(INCLUDE) -Wno-deprecated -c -o $@ $< 

.c.o:
	gcc $(CXXFLAGS) -c -o $@ $<

src := main.cpp
src += http_server.cpp


obj := $(src:.cpp=.o)

all : $(obj)
	g++ -o main $(INCLUDE) $(obj) $(LIBDIR) $(LIB) 

clean: $(obj)
	rm -f *.o
	rm -f main
