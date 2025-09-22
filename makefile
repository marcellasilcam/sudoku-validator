EXEC = exe
CC = gcc
CFLAGS = -Wall -std=c11

all: $(EXEC)

$(EXEC): main.o TAD.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c TAD.h
	$(CC) $(CFLAGS) -c main.c

TAD.o: TAD.c TAD.h
	$(CC) $(CFLAGS) -c TAD.c

clean:
	rm -f $(EXEC) *.o