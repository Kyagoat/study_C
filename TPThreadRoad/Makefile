CC = gcc
CLFLAGS = -Wall -Wextra -pthread -I${LD_LIBRARY_PATH}
LDFLAGS = -L${LD_LIBRARY_PATH} -lroad -lallegro -lallegro_primitives
LD_LIBRARY_PATH =/users/but/info/Public/Systeme/onTheRoad/

all: onTheRoad onTheRoad2 onTheRoad3 onTheRoad4

onTheRoad : onTheRoad.c
	$(CC) $(CLFLAGS) -o onTheRoad onTheRoad.c $(LDFLAGS)

onTheRoad2 : onTheRoad2.c
	$(CC) $(CLFLAGS) -o onTheRoad2 onTheRoad2.c $(LDFLAGS)

onTheRoad3 : onTheRoad3.c
	$(CC) $(CLFLAGS) -o onTheRoad3 onTheRoad3.c $(LDFLAGS)

onTheRoad4 : onTheRoad4.c
	$(CC) $(CLFLAGS) -o onTheRoad4 onTheRoad4.c $(LDFLAGS)

clean:
	rm -f onTheRoad onTheRoad2 onTheRoad3 onTheRoad4
