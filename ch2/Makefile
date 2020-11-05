CXX ?= dpcpp
CXXFLAGS ?= -std=c++17

SRCS := $(wildcard *.cpp)
PRGS := $(patsubst %.cpp,%,$(SRCS))
RUN := $(addprefix run_, $(PRGS))

.PHONY: all
all: $(PRGS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

run_%:%
	./$^

.PHONY: clean
clean:
	rm -rf $(PRGS)