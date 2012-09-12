CC=gcc
FLAGS=-Os -pedantic -Wall

all: EventEngine WorkflowEngine Utils test


test: EventEngine WorkflowEngine Utils
	$(CC) $(FLAGS) main.c -o main eventengine.o workflowengine.o utils.o

EventEngine: EventEngine.c
	$(CC) $(FLAGS) -c EventEngine.c -o eventengine.o
	
WorkflowEngine: WorkflowEngine.c
	$(CC) $(FLAGS) -c WorkflowEngine.c -o workflowengine.o

Utils: Utils.c
	$(CC) $(FLAGS) -c Utils.c -o utils.o

clean:
	rm *.o main
