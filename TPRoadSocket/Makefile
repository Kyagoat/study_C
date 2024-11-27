CC = gcc
CLFLAGS = -Wall -Wextra -pthread -I${LD_LIBRARY_PATH}
LDFLAGS = -L${LD_LIBRARY_PATH} -lroad -lallegro -lallegro_primitives
LD_LIBRARY_PATH =/users/but/info/Public/Systeme/onTheRoad/

all: onTheRoad3

onTheRoad3 : onTheRoad3.c Reseau.o
	$(CC) $(CLFLAGS) -o onTheRoad3 onTheRoad3.c Reseau.o $(LDFLAGS)

Reseau.o: Reseau.c Reseau.h
	$(CC) $(CLFLAGS) -c Reseau.c
clean:
	rm -f onTheRoad3 Reseau