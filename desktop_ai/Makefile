CC := g++
# selects all the files that end with .cpp in src/
SRC := $(wildcard src/*.cpp)
# replaces the .cpp with .o
OBJ := $(SRC:src/%.cpp=obj/%.o)

EXE := checkersai
# -Iinclude flag includes all header files 
# in include/ directory in the compilation process
CFLAGS := -Wall -O2 -std=c++11 -Iinclude

# links all objects into the executable server
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

# compiles all source files from src/ into object files
# and places them in the obj/ directory
obj/%.o: src/%.cpp | obj
	$(CC) $(CFLAGS) -c $< -o $@

# creates obj directory if not yet created
obj:
	mkdir obj

# removes all object files and the executable
clean:
	@rm $(OBJ) $(EXE)
	@rmdir obj