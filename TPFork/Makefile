CC = gcc
CLFLAGS = -Wall -Wextra

all: fork forkSync

forkSync: forkSync.c
	$(CC) $(CLFLAGS) -o forkSync forkSync.c

fork: fork.c
	$(CC) $(CLFLAGS) -o fork fork.c

clean:
	rm -f fork forkSync