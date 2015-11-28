CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wno-c++11-extensions

OBJ_DIR = bin
LIB_DIR = -L/usr/lib
INC_DIR = -I/usr/include -I../lib

SOURCE = $(wildcard *.cc)
OBJECTS = ${SOURCE:%.cc=$(OBJ_DIR)/%.o}
EXECUTABLES = ${SOURCE:%.cc=$(OBJ_DIR)/%.out}

.PHONY: init clean demo

# put this as the first target,so that it will be the default target
all: init $(EXECUTABLES)

$(OBJ_DIR)/%.out:%.cc
	$(CXX) $(CXXFLAGS) $(INC_DIR) $(LIB_DIR) $< -g -o $@

# prefix command with @ to suppress command line echo
init:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -fr $(OBJ_DIR)

demo:
	@echo "there is just a sample to demonstrate .PHONY usage." \
	"If there is a file named demo, make demo won't execute"
