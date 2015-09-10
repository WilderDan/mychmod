CC=gcc
CFLAGS=-c -Wall -g

SOURCES=$(wildcard src/*.c)
OBJECTS=$(notdir $(SOURCES:.c=.o))

EXECUTABLE=mychmod

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)  
	$(CC) $(OBJECTS) -o $(EXECUTABLE) 

%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm $(OBJECTS) $(EXECUTABLE)
