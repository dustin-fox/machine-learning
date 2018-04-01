BIN = nn

CXX=g++
SHELL=/bin/sh

CPPFLAGS=-O3 -Wall
CFLAGS=$(CPPFLAGS)
LIBS = -lm

SRCS=\
nn.cpp\
perceptron.cpp\
mat.cpp\
randf.cpp

HDRS=\
perceptron.h\
lib/mat.h\
lib/rand.h

OBJS=\
perceptron.o\
../lib/mat.o\
../lib/rand.o

$(BIN): $(OBJS) $(BIN).o
	$(CXX)  $(CFLAGS) $(OBJS) $(BIN).o $(LIBS) -o $(BIN)

$(BIN)oneof: $(OBJS) $(BIN)oneof.o
	$(CXX)  $(CFLAGS) $(OBJS) $(BIN)oneof.o $(LIBS) -o $(BIN)oneof

clean:
	/bin/rm -f *.o a.out $(BIN) $(BIN)oneof