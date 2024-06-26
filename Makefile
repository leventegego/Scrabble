CC = gcc
COMPILEROPTIONS = -g -Wall
LINKEROPTIONS =
NAME = Scrabble

INCLUDE =
LIB =
LIBS =

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))
OUT = bin/$(NAME).exe

build: $(OBJS) link

link:
	@echo linking $(OBJS)
	$(CC) -o $(OUT) $(LINKEROPTIONS) $(OBJS) $(LIB) $(LIBS)

obj/%.o: src/%.c
	@echo compiling $<
	$(CC) -o $@ -c $(COMPILEROPTIONS) $< $(INCLUDE)

print:
	@echo srcs: $(SRCS)
	@echo objs: $(OBJS)
	@echo out: $(OUT)

reset:
	-rm -rf obj/*