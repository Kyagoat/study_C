CC = gcc
CLFLAGS = -Wall -Wextra -pthread -I${LD_LIBRARY_PATH}
LDFLAGS = -L${LD_LIBRARY_PATH} -lroad -lallegro -lallegro_primitives
LD_LIBRARY_PATH =/users/but/info/Public/Systeme/onTheRoad/

all: RoadSocketIn

RoadSocketIn : RoadSocketIn.c Reseau.o
	$(CC) $(CLFLAGS) -o RoadSocketIn RoadSocketIn.c Reseau.o $(LDFLAGS)

Reseau.o: Reseau.c Reseau.h
	$(CC) $(CLFLAGS) -c Reseau.c
clean:
	rm -f RoadSocketIn Reseau