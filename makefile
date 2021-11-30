main.out: main.cpp helper.cpp helper.h
	g++ -std=c++11  -o main.out main.cpp helper.cpp

clean:
	rm -f main.out helper.o