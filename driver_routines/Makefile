CFLAGS=-O3 -std=c++17
INCLUDE=-I ../src/
LDFLAGS=../src/*.o
CC=c++

all: graph nature obs pf

graph: graph.cpp

test: test_driver.cpp


nature: nature.cpp

obs: obs.cpp

pf: pf.cpp


%: %.cpp 
	$(CC) $(CFLAGS) $^ $(INCLUDE) $(LDFLAGS) -o $@

