.PHONY: clean test
.PRECIOUS: $(PATHB)test_%.out
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

CC	= gcc
CXX	= g++

FLAGS	= -c

PATHU	= Unity/src/
PATHS	= src/
PATHI	= inc/
PATHT	= test/
PATHB	= build/
PATHD	= build/depends/
PATHO	= build/objs/
PATHR	= build/results/

SRCS	= $(wildcard $(PATHS)*.cpp) 
SRCT	= $(wildcard $(PATHT)*.cpp) 

OBJ	= $(patsubst $(PATHS)%.cpp,$(PATHO)%.o,$(SRCS))
INC	= -I. -I$(PATHU) -I$(PATHI)

TRGT  	= $(PATHB)libloogy.a 
LIBS 	= 

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)
RESULTS	= $(patsubst $(PATHT)%.cpp,$(PATHR)%.txt,$(SRCT))


default: $(TRGT)


$(PATHB):
	mkdir -p $(PATHB)


$(PATHD):
	mkdir -p $(PATHD)


$(PATHO):
	mkdir -p $(PATHO)


$(PATHR):
	mkdir -p $(PATHR)


$(PATHR)%.txt: $(PATHB)%.out
	./$< > $@ 2>&1


#$(PATHB)test_%.out: $(PATHO)test_%.o $(PATHO)%.o $(PATHO)unity.o $(PATHD)test_%.d
$(PATHB)test_%.out: $(PATHO)test_%.o $(PATHO)%.o $(PATHO)unity.o $(OBJ)
	$(CXX) $(INC) -DTEST -o $@ $^


$(PATHO)%.o:: $(PATHT)%.cpp
	$(CXX) $(FLAGS) $(INC) -DTEST $< -o $@


$(PATHO)%.o:: $(PATHS)%.cpp
	$(CXX) $(FLAGS) $(INC) -DTEST $< -o $@


$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(CC) $(FLAGS) $(INC) -DTEST $< -o $@


$(PATHD)%.d:: $(PATHT)%.c
	$(CC) -MM -MG -MF $@ $<


$(PATHD)%.d:: $(PATHT)%.cpp
	$(CXX) -MM -MG -MF $@ $<



$(TRGT) : $(BUILD_PATHS) $(OBJ) 
	ar rcs $@ $(OBJ) 

clean:
	@rm -r $(PATHB)


test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------IGNORES:-----------------------"
	@echo `grep -s IGNORE $(PATHR)*.txt`
	@echo "-----------------------FAILURES:-----------------------"
	@echo `grep -s FAIL $(PATHR)*.txt`
	@echo "DONE"
