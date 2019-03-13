out:main.o test.o
	g++ main.o test.o -o out
main.o:main.cpp
	g++ -c main.cpp
test.o:test.cpp
	g++ -c test.cpp
.PHONY clean:
	rm -f *.o