CXX = g++

all: test runtest

.cpp.o:
	$(CXX) -c $< -I../include $(CXXFLAGS)

test: test.o utest.o
	$(CXX) -o $@ $^ -llua $(CXXFLAGS)

runtest: test
	./test


