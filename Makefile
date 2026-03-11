CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Wall -Wno-unused-function
TARGET = mytho.exe

all: $(TARGET)

$(TARGET): lex.yy.c mytho.tab.c
	$(CC) $(CFLAGS) lex.yy.c mytho.tab.c -o $(TARGET) -lfl

mytho.tab.c mytho.tab.h: mytho.y
	$(BISON) -d mytho.y

lex.yy.c: mytho.l mytho.tab.h
	$(FLEX) mytho.l

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f lex.yy.c mytho.tab.c mytho.tab.h $(TARGET) output.txt