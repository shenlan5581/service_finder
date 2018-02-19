
BASEDIR :=.

INCLUDE := -I$(BASEDIR)/
INCLUDE += -I$(BASEDIR)/deps/libevent/include

LIBDIR := -L$(BASEDIR)/
LIBDIR += -L$(BASEDIR)/deps/libevent/lib 
LIBDIR += -L$(BASEDIR)/deps/json

 
LIB := -levent -ljsoncpp -lpthread
 
src := main.cpp 
src += client.cpp
	 		
obj := $(src:.cpp=.o)

.cpp.o:
	g++ $(INCLUDE) -c -g -o $@ $<

run:all
	./main

all: $(obj)
	g++ -g -o main $(INCLUDE) $(LIBDIR) $(obj) $(LIB) -Wl,-rpath,./deps/libevent/lib/   -fPIC
	 
clean:$(obj)
	rm -f *.o
	rm -f main