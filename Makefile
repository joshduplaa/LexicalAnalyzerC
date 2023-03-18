CC = gcc
CFLAGS = -Wall -g

dcooke_analyzer: lexicalanalyzer.o
	$(CC) $(CFLAGS) -o dcooke_analyzer lexicalanalyzer.o

lexicalanalyzer.o: lexicalanalyzer.c test.dc
	$(CC) $(CFLAGS) -c lexicalanalyzer.c

clean:
	rm -f *.o dcooke_analyzer