#DB_SRC = eval_ast.cpp database.cpp table.cpp db_one.cpp main.cpp query_result.cpp
#OBJS = exe/main.o db_one.o database.o query_result.o
CXXFLAGS = -g -Werror -Wall
OBJS = eval_ast.o database.o table.o db_one.o main.o query_result.o types.o
all: db_one
#	$(CC) $(CFLAGS) -o db $(OBJS)
#fb3-1: fb3-1.l fb3-1.y fb3-1.h
#	bison -d fb3-1.y
#	flex -ofb3-1.lex.c fb3-1.l
#	gcc -o $@ fb3-1.tab.c fb3-1.lex.c fb3-1funcs.c
db_one: parser $(OBJS)
	g++ -o db_one *.o
#	g++ -g -c $(DB_SRC) 
parser: mysql.l mysql.y sqlfuncs.h sqlfuncs.cpp
	bison -t -d mysql.y
	flex -omysql.lex.c  --header-file=mysql.lex.h  mysql.l
	g++ -DYYDEBUG=1 -g -c  mysql.tab.c mysql.lex.c sqlfuncs.cpp
clean:
	rm -f  *.o  mysql.tab.c mysql.lex.c mysql.tab.h mysql.lex.h
