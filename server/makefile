ifeq ($(make_basedir),) 
	make_basedir := ..
endif

CXXFLAGS := -g -std=c++11

INCLUDE := -I$(make_basedir)/
INCLUDE += -I$(make_basedir)/deps

LIBDIR := -L$(make_basedir)/deps
LIBDIR += -L$(make_basedir)/deps/libevent/lib 

LIB := -levent -lpthread

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
