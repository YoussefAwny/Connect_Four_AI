CC=g++
CFLAGS=-Wall -std=c++11
EXE=test.exe
BUILD_DIR=build
EXE_PATH=$(BUILD_DIR)/$(EXE)
OBJ_DIR=$(BUILD_DIR)/obj
SRC=$(wildcard *.cpp)

# include the source files themselves 
# except main.cpp,
# note that their object files will be
# build in "$(OBJ_DIR)/.." due to the
# double dots ".."
SRC+=../state.cpp ../abs.cpp
OBJ=$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: make_dirs $(EXE_PATH)

# you will have to use "make clean" after "make debug"
# if you want to force rebuild without -g flag
debug: CFLAGS +=-g
debug: make_dirs $(EXE_PATH)

make_dirs: | $(BUILD_DIR) $(OBJ_DIR)

$(BUILD_DIR):
	-mkdir $(subst /,\,$@)

$(OBJ_DIR):
	-mkdir $(subst /,\,$@)

$(EXE_PATH): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

run: all
	$(EXE_PATH)

.phony: clean
clean:
	-del /S /Q $(BUILD_DIR)\*

test_makefile:
	@echo SRC=$(SRC)
	@echo OBJ=$(OBJ)
	@echo EXE=$(EXE)
	@echo BUILD_DIR=$(BUILD_DIR)
	@echo OBJ_DIR=$(OBJ_DIR)
	@echo EXE_PATH=$(EXE_PATH)
