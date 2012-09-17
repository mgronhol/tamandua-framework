CC=gcc
FLAGS=-Os -pedantic -Wall -I ./includes/

all: EventEngine WorkflowEngine Utils Emulator test


test: EventEngine WorkflowEngine Utils Emulator
	$(CC) $(FLAGS) src/main.c -o main src/eventengine.o src/workflowengine.o src/utils.o src/emulator.o -lpthread

EventEngine: src/EventEngine.c
	$(CC) $(FLAGS) -c src/EventEngine.c -o src/eventengine.o
	
WorkflowEngine: src/WorkflowEngine.c
	$(CC) $(FLAGS) -c src/WorkflowEngine.c -o src/workflowengine.o

Utils: src/Utils.c
	$(CC) $(FLAGS) -c src/Utils.c -o src/utils.o

Emulator: src/Emulator.c
	$(CC) $(FLAGS) -c src/Emulator.c -o src/emulator.o

clean:
	rm src/*.o main
