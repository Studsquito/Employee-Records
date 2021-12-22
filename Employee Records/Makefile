CC = gcc
FLAGS = -Wall -std=c99 -pedantic
OBJECTS = main.o functions.o

driver: $(OBJECTS)
	$(CC) $(FLAGS) -o driver $(OBJECTS)

main.o: main.c
	$(CC) $(FLAGS) -c main.c -o main.o

functions.o: functions.c
	$(CC) $(FLAGS) -c functions.c -o functions.o

clean:
	rm -f $(OBJECTS) driver