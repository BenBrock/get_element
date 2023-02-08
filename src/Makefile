
CXX = g++

SOURCES += $(wildcard *.cpp)
TARGETS := $(patsubst %.cpp, %, $(SOURCES))

CXXFLAGS = -std=c++23 -I../include

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LD_FLAGS)

clean:
	rm -fv $(TARGETS)
