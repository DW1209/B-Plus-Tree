CXX = g++
CFLAGS = -std=c++17 -O3

bplustree: main.cpp utils.cpp index.cpp
	$(CXX) $(CFLAGS) -o $@ main.cpp utils.cpp index.cpp

clean:
	rm -r bplustree
