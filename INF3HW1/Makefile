CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGETS = functional_test performance_test

all: $(TARGETS)

functional_test: functional_test.cpp SmartPtr.h
	$(CXX) $(CXXFLAGS) -o $@ functional_test.cpp

performance_test: performance_test.cpp SmartPtr.h
	$(CXX) $(CXXFLAGS) -o $@ performance_test.cpp

clean:
	del $(TARGETS).exe 2>nul || rm -f $(TARGETS)
