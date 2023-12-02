CC = g++
CFLAGS = -std=c++11 $(shell pkg-config --cflags opencv4)
LIBS = $(shell pkg-config --libs opencv4)

all: secuencial paralelo_thread paralelo_openMP

secuencial: secuencial_carpeta/secuencial.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

paralelo_thread: paralelo_thread_carpeta/paralelo_thread.cpp
	$(CC) $(CFLAGS) -pthread $< -o $@ $(LIBS)

paralelo_openMP: paralelo_openMP_carpeta/paralelo_openMP.cpp
	$(CC) $(CFLAGS) -fopenmp $< -o $@ $(LIBS)

clean:
	rm -f secuencial paralelo_thread paralelo_openMP
