obj = main.o connect.o service_finder_c.o  


run:main
	./main
main:$(obj)
	g++ -o main $(obj)  

main.o:main.cpp
	g++ -c -o main.o main.cpp
connect.o:connect.cpp
	g++ -c -o connect.o connect.cpp
service_finder.o:service_finder_c.cpp
	g++ -c -o  service_finder_c.o  service_finder_c.cpp
pthread_work.o:pthread_work.cpp
	g++ -c -o phtread_work.o pthread_work.cpp
	