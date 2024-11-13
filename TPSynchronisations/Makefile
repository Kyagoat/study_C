CC = gcc
CLFLAGS = -Wall -Wextra -pthread -I${LD_LIBRARY_PATH}
LDFLAGS = -L${LD_LIBRARY_PATH} -lroad -lallegro -lallegro_primitives
LD_LIBRARY_PATH =/users/but/info/Public/Systeme/onTheRoad/

all: stillOnTheRoadQ1.1 stillOnTheRoadQ1.2

stillOnTheRoadQ1.1 : stillOnTheRoadQ1.1.c
	$(CC) $(CLFLAGS) -o stillOnTheRoadQ1.1 stillOnTheRoadQ1.1.c $(LDFLAGS)

stillOnTheRoadQ1.2 : stillOnTheRoadQ1.2.c
	$(CC) $(CLFLAGS) -o stillOnTheRoadQ1.2 stillOnTheRoadQ1.2.c $(LDFLAGS)

clean:
	rm -f stillOnTheRoadQ1.1 stillOnTheRoadQ1.2