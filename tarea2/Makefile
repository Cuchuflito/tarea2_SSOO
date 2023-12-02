CC=g++
CFLAGS=-std=c++11 $(shell pkg-config --cflags opencv4)
LIBS=$(shell pkg-config --libs opencv4)

all: paralelo_openMP paralelo_thread secuencial

paralelo_openMP: paralelo_openMP.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

paralelo_thread: paralelo_thread.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

secuencial: secuencial.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f paralelo_openMP paralelo_thread secuencial
