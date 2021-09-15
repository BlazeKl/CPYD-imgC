CXX = g++
CXXFLAGS = -I/usr/include/opencv4 -std=c++11 -Wall -g3 -O2 -fopenmp
EXT = -lm

dir:
	mkdir -p build dist

clean:
	rm -fr *.o a.out build dist

main.o:
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

compile: clean dir main.o
	$(CXX) $(CXXFLAGS) -o dist/test build/main.o $(EXT)

.DEFAULT_GOAL := compile
