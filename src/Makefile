CXX = g++
CXXFLAGS = -ggdb

all: test runtest

.cpp.o: 
	$(CXX) -c $< -I../include $(CXXFLAGS)

test.o : ../include/*.hpp

test: test.o utest.o
	$(CXX) -o $@ $^ -llua $(CXXFLAGS)

runtest: test
	./test

clean:
	rm *.o
