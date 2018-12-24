#Lan Anh Do ld9hu Makefile lab10 11/27/18
CXX = clang++ $(CXXFLAGS)
CXXFLAGS = -Wall -O2
DFILES =  huffmandec.o node.o
EFILES = heap.o  huffmanenc.o node.o

.SUFFIXES: .o .cpp

all: encoder decoder
	
encoder: $(EFILES)
	$(CXX) -o encoder $(EFILES)
	
decoder: $(DFILES)
	$(CXX) -o decoder $(DFILES)

clean:
	-rm -f *.o *~ output
	
node.o: node.cpp node.h
	$(CXX) -c node.cpp
	
heap.o: heap.cpp heap.h
	$(CXX) -c heap.cpp
	
