CXX = g++
CFLAGS = -std=c++17 -O3

bplustree: main.o utils.o index.o
	$(CXX) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

clean:
	rm -r bplustree
