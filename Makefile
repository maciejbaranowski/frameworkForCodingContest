all: debug release
debug: io.h algorithm.h utils.h main.cpp
	g++ -std=c++17 -o debug main.cpp -Wall -g -Og
release: io.h algorithm.h utils.h main.cpp
	g++ -std=c++17 -o release main.cpp -Wall -O3 -march=native -flto
