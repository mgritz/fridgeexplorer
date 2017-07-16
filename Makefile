
fridgeexplorer: main.cpp dbiface.cpp
	g++ -Wall dbiface.cpp main.cpp -o fridgeexplorer

all: fridgeexplorer

clean:
	rm fridgeexplorer
