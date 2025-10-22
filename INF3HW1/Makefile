CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGETS = functional_test performance_test interactive_console

all: $(TARGETS)

functional_test: functional_test.cpp SmartPtr.h
	$(CXX) $(CXXFLAGS) -o $@ functional_test.cpp

performance_test: perfomance_test.cpp SmartPtr.h
	$(CXX) $(CXXFLAGS) -o $@ perfomance_test.cpp

interactive_console: interactive_console.cpp SmartPtr.h
	$(CXX) $(CXXFLAGS) -o interactive_console interactive_console.cpp
clean:
	del $(TARGETS).exe 2>nul || rm -f $(TARGETS)
