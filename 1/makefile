

#compiler
CXX:=g++

#C++ standard
CXXFLAGS+=-std=c++14

#FLAGS
CXXFLAGS+=-Wall

testmtl: testmtl.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

ex1_mtl: mat2.o ex1.o
	$(LINK.cpp) $^ -o $@

ex2_1: mat.o ex2_1.o
	$(LINK.cpp) $^ -o $@

ex1: mat.o ex1.o
	$(LINK.cpp) $^ -o $@

%.o:%.cpp
	$(COMPILE.cpp) $< -o $@

clean:
	-rm *.o
	-rm ex1
.PHONY:clean
