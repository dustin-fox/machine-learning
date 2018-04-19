CC=g++
OPTS=-g -Wall -std=c++11
BIN=kdtree
SOURCES=kdtree.cpp lib/mat.cpp lib/randmt.cpp
OBJECTS=$(SOURCES:.cpp=.o)
$(BIN) : $(OBJECTS)
	$(CC) $(OPTS) $^ -o $@
$(OBJECTS): %.o : %.cpp
	$(CC) -c $(OPTS) $^ -o $@
clean:
	rm $(OBJECTS) $(BIN)