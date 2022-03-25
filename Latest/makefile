

CC = gcc

all:Scheduler 

Scheduler:main display file
	${CC} -o Scheduler main.o display.o file.o

main:
	${CC} -c main.c
display:
	${CC} -c display.c
file:
	${CC} -c file.c

clean:*.o 
	rm *.o
	rm Scheduler main
