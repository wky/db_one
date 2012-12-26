CC = g++
CFLAGS = -g -O0
#OBJS = exe/main.o db_one.o database.o query_result.o
all: db_one
#	$(CC) $(CFLAGS) -o db $(OBJS)
fb3-1: fb3-1.l fb3-1.y fb3-1.h
	bison -d fb3-1.y
	flex -ofb3-1.lex.c fb3-1.l
	gcc -o $@ fb3-1.tab.c fb3-1.lex.c fb3-1funcs.c
db_one: database.cpp table.cpp db_one.cpp main.cpp query_result.cpp parser
	g++ -g -c database.cpp table.cpp db_one.cpp main.cpp query_result.cpp
	g++ -g -o db_one *.o
parser: mysql.l mysql.y sqlfuncs.h sqlfuncs.cpp
	bison -t -d mysql.y
	flex -omysql.lex.c  --header-file=mysql.lex.h  mysql.l
	g++ -DYYDEBUG=1 -g -c  mysql.tab.c mysql.lex.c sqlfuncs.cpp
clean:
	rm -f  *.o  mysql.tab.c mysql.lex.c mysql.tab.h mysql.lex.h
