CC=g++
OPTS=-g -Wall -std=c++11
BIN=pca
SOURCES=pca.cpp lib/mat.cpp lib/randmt.cpp
OBJECTS=$(SOURCES:.cpp=.o)
$(BIN) : $(OBJECTS)
	$(CC) $(OPTS) $^ -o $@
$(OBJECTS): %.o : %.cpp
	$(CC) -c $(OPTS) $^ -o $@
clean:
	rm $(OBJECTS) $(BIN)
	rm z-before.ppm z-after.ppm