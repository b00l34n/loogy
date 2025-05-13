.PHONY:

CC     = g++
SRC   := $(wildcard src/*.cpp) 
TRGT  := build/main
LIBS  := 
FLAGS := -g 

default: all

all: $(SRC)
	@mkdir -p build
	$(CC) $(FLAGS) $(LIBS) -I./inc/ -o $(TRGT) $^

test:
	@$(TRGT)

debug: $(SRC)
	@mkdir -p build
	$(CC) $(FLAGS) -DDEBUG $(LIBS) -I./inc/ -o $(TRGT) $^

db:
	gdb $(TRGT)

clean:
	@rm -r build/


