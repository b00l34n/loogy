.PHONY:

CC     = g++
LIBS  := 
FLAGS := -g -c 

SRC   := $(wildcard src/*.cpp) 
OBJ   := $(SRC:.cpp=.o)
TRGT  := lib/logger.a

default: all

all: $(TRGT)
build: $(TRGT)

$(TRGT): $(OBJ)
	@mkdir -p lib 
	ar rvs $@ $^ 

%.o: %.cpp 
	@mkdir -p build
	$(CC) $(FLAGS) $< $(LIBS) -I./inc/ -o $@

debug: $(SRC)
	@mkdir -p build
	$(CC) $(FLAGS) -DDEBUG $(LIBS) -I./inc/ -o $(TRGT) $^

clean:
	@rm -rf build/
	@rm -rf lib/

