CC = g++
CFLAGS = -g -O0
#OBJS = exe/main.o db_one.o database.o query_result.o
#all: $(OBJS)
#	$(CC) $(CFLAGS) -o db $(OBJS)
fb3-1: fb3-1.l fb3-1.y fb3-1.h
	bison -d fb3-1.y
	flex -ofb3-1.lex.c fb3-1.l
	gcc -o $@ fb3-1.tab.c fb3-1.lex.c fb3-1funcs.c
mysql: mysql.l mysql.y sqlfuncs.h
	bison -d mysql.y
	flex -omysql.lex.c mysql.l
	g++ -o mysql mysql.tab.c mysql.lex.c sqlfuncs.c
clean:
	rm $(OBJS) db
