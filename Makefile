all: add-nbo

add-nbo: main.cpp
	g++ -o add-nbo main.cpp -lws2_32
