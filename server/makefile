obj = main.o  database.o
src = main.cpp  database.cpp  
run:main
	./main
main:$(obj)
	g++  -o main $(obj)  -lmysqlclient  
main.o:main.cpp 
	g++ -c -o main.o main.cpp 
service_finder_s.o:service_finder_s.cpp
	g++ -c -o  service_finder_s.o  service_finder_s.cpp
pthread_work.o:pthread_work.cpp
	g++ -c -o phtread_work.o pthread_work.cpp
http_request.o:http_request.cpp
	g++ -c -o http_request.o http_request.cpp
database.o:database.cpp
	g++ -c -o database.o database.cpp
	
clean:$(obj)
	rm $(obj)


gdb:debug
	gdb debug 

debug:$(src)
	g++ -g -o debug  $(src) -lmysqlclient  

	
