CC = gcc
CLFLAGS = -Wall -Wextra

all: firstPPM gradient copy darker arguments binaryPPM tuner

tuner: tuner.c
	$(CC) $(CLFLAGS) -o tuner tuner.c

binaryPPM : binaryPPM.c
	$(CC) $(CLFLAGS) -o binaryPPM binaryPPM.c 

arguments : arguments.c
	$(CC) $(CLFLAGS) -o arguments arguments.c 

darker : darker.c
	$(CC) $(CLFLAGS) -o darker darker.c 

copy : copy.c
	$(CC) $(CLFLAGS) -o copy copy.c 

gradient : gradient.c
	$(CC) $(CLFLAGS) -o gradient gradient.c 

firstPPM : firstPPM.c
	$(CC) $(CLFLAGS) -o firstPPM firstPPM.c 

clean:
	rm -f firstPPM gradient copy darker arguments binaryPPM tuner