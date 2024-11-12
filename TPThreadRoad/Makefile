CC = gcc
CLFLAGS = -Wall -Wextra -pthread -I${LD_LIBRARY_PATH}
LDFLAGS = -L${LD_LIBRARY_PATH} -lroad -lallegro -lallegro_primitives
LD_LIBRARY_PATH =/users/but/info/Public/Systeme/onTheRoad/

all: onTheRoad onTheRoad2

onTheRoad : onTheRoad.c
	$(CC) $(CLFLAGS) -o onTheRoad onTheRoad.c $(LDFLAGS)

onTheRoad2 : onTheRoad2.c
	$(CC) $(CLFLAGS) -o onTheRoad2 onTheRoad2.c $(LDFLAGS)