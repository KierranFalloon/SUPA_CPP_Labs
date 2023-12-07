# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra # debugging flags
OBJ_DIR = build
SRC = .
SRC_FILES = $(wildcard $(SRC)/*.cxx) # all .cpp files in src
OBJ_FILES = $(patsubst $(SRC)/%.cxx, $(OBJ_DIR)/%.o, $(SRC_FILES)) # all .o files in build corresponding to .cpp files in src
OUTPUT = EstimatePi.out

# make all: creates a build/ directory, compiles the .cxx files in current directory and links the corresponding .o files into an executable
# make clean: removes all built files and the build/ directory
all: $(OBJ_DIR)/$(OUTPUT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC)/%.cxx | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(OUTPUT): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)/*
	rmdir $(OBJ_DIR)
