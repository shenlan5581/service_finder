obj = main.o connect.o  


run:main
	./main
main:$(obj)
	g++ -o main $(obj)  

main.o:main.cpp
	g++ -c -o main.o main.cpp
connect.o:connect.cpp
	g++ -c -o connect.o connect.cpp
 