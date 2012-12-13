CC = g++
FLAGS = -g -O0
OBJS = main.o
all: $(OBJS)
	$(CC) $(FLAGS) -o db $(OBJS)
clean:
	rm *.o db
