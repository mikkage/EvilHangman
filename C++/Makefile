#Makefile for Red Black Tree
#Compiler: g++
#Based on sample makefile found at
#http://www.digitalmars.com/d/archives/c++/Simple_Make_File_5844.html

CC=g++
SRC=hangman.cpp hangman.h main.cpp
CFLAGS=
LINK=
INCLUDE=
EXE=hangman
RM=del

OBJS=$(SRC:.cpp=.obj)
MAPS=$(SRC:.cpp=.map)

all:${OBJS}
	${CC} ${OBJS} ${LINK} -o ${EXE}

%.obj: %.cpp
	${CC} ${INCLUDE} ${CFLAGS} -c $*.cpp -o $*.obj

clean:
	- ${RM} ${EXE}
	- ${RM} ${OBJS}
	- ${RM} ${MAPS}

tidy: all
	- ${RM} ${OBJS}
	- ${RM} ${MAPS}

rebuild: clean all