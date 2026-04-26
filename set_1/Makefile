CC = gcc
OBJS = main.o EX_1.o EX_2.o EX_3.o


all: main

main: $(OBJS)
	$(CC) $(OBJS) -o main

main.o: main.c EX_1.h EX_2.h EX_3.h
	$(CC) -c main.c

EX_1.o: EX_1.c EX_1.h
	$(CC) -c EX_1.c

EX_2.o: EX_2.c EX_2.h
	$(CC) -c EX_2.c

EX_3.o: EX_3.c EX_3.h
	$(CC) -c EX_3.c

clean:
	rm -f main $(OBJS)