CC = gcc
FLAGS = -Wall -g -w
OBJECTS =  ActiveObject.c threadsQueue.c st_pipeline.c
HEADERS = ActiveObject.h Queue.h st_pipeline.h

all:st_pipeline 

st_pipeline: $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) -o st_pipeline $(OBJECTS)

clean:
	rm st_pipeline