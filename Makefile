.PHONY:

CXX	= g++
FLAGS	= -c

SRC	= $(wildcard src/*.cpp) 
OBJ	= $(SRC:.cpp=.o)
BOBJ	= $(wildcard build/*.o)
INC	= -I./inc/

TRGT  	= libloogy.a 
LIBS 	= 

default: $(TRGT)

%.o: %.cpp
	$(CXX) $(FLAGS) $(INC) $< -o build/$(notdir $@) 
	

$(TRGT) : mkdir $(OBJ) 
	ar rcs $@ $(BOBJ) 

mkdir:
	@mkdir -p build/

clean:
	@rm -r build/


