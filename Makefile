#DB_SRC = eval_ast.cpp database.cpp table.cpp db_one.cpp main.cpp query_result.cpp
#OBJS = exe/main.o db_one.o database.o query_result.o
CXXFLAGS = -O -Wall -Wextra  -Wno-sign-compare -Wno-unused-parameter
OBJS = eval_ast.o display.o database.o table.o db_one.o main.o query_result.o types.o sqlfuncs.o
all: db_one
#	$(CC) $(CFLAGS) -o db $(OBJS)
#fb3-1: fb3-1.l fb3-1.y fb3-1.h
#	bison -d fb3-1.y
#	flex -ofb3-1.lex.c fb3-1.l
#	gcc -o $@ fb3-1.tab.c fb3-1.lex.c fb3-1funcs.c
db_one: parser $(OBJS)
	c++ $(CXXFLAGS) -o db_one *.o
#	g++ -g -c $(DB_SRC) 
parser: mysql.l mysql.ypp
	bison -t --defines=mysql.tab.h mysql.ypp
	flex -omysql.lex.cpp --header-file=mysql.lex.h  mysql.l
	c++ $(CXXFLAGS) -c -o mysql.tab.o mysql.tab.cpp
	c++ $(CXXFLAGS) -c -o mysql.lex.o mysql.lex.cpp
clean:
	rm -f  *.o  mysql.tab.cpp mysql.lex.cpp mysql.tab.h mysql.lex.h
