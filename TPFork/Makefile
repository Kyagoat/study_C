CC = gcc
CLFLAGS = -Wall -Wextra

all: fork forkSync forkGlobales forkShared

forkShared: forkShared.c
	$(CC) $(CLFLAGS) -o forkShared forkShared.c

forkGlobales: forkGlobales.c
	$(CC) $(CLFLAGS) -o forkGlobales forkGlobales.c

forkSync: forkSync.c
	$(CC) $(CLFLAGS) -o forkSync forkSync.c

fork: fork.c
	$(CC) $(CLFLAGS) -o fork fork.c

clean:
	rm -f fork forkSync forkGlobales forkShared