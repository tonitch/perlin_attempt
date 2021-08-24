CC=g++

CFLAGS= -Wall -g
LDLIBS= -lSDL2  -lSDL2_image -lSDL2_ttf -lm

SOURCES= $(wildcard *.cpp)

all: main

main: $(SOURCES) 
	$(CC) $(CFLAGS) -o main $(SOURCES) $(LDLIBS)

clean: 
	$(RM) main *.o *~

run: main
	./main

.PHONY: all clean run
