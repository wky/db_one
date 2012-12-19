CC = g++
CFLAGS = -g -O0
OBJS = exe/main.o db_one.o database.o query_result.o
all: $(OBJS)
	$(CC) $(CFLAGS) -o db $(OBJS)
fb3-1: fb3-1.l fb3-1.y fb3-1.h
	bison -d fb3-1.y
	flex -ofb3-1.lex.c fb3-1.l
	gcc -o $@ fb3-1.tab.c fb3-1.lex.c fb3-1funcs.c
clean:
	rm $(OBJS) db
