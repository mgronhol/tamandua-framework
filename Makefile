CC=gcc
FLAGS=-Os -pedantic -Wall -I ./includes/

all: EventEngine WorkflowEngine Utils test


test: EventEngine WorkflowEngine Utils
	$(CC) $(FLAGS) src/main.c -o main src/eventengine.o src/workflowengine.o src/utils.o

EventEngine: src/EventEngine.c
	$(CC) $(FLAGS) -c src/EventEngine.c -o src/eventengine.o
	
WorkflowEngine: src/WorkflowEngine.c
	$(CC) $(FLAGS) -c src/WorkflowEngine.c -o src/workflowengine.o

Utils: src/Utils.c
	$(CC) $(FLAGS) -c src/Utils.c -o src/utils.o

clean:
	rm src/*.o main
