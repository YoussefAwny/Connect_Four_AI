# - makefile assumes Windows OS (uses backslashes for paths)
# - does not detect changes to header files (*.h),
#   use "make clean" before re-building
#
# quick start guide:
# 	make 				- to build all files
#	make run 			- to bulid all files and run the exe
#	make clean 			- to clean all build files
#	make test_makefile 	- to output the variables used in the makefile

CC=g++
CFLAGS=-Wall -std=c++11
EXE=game.exe
BUILD_DIR=build
EXE_PATH=$(BUILD_DIR)/$(EXE)
OBJ_DIR=$(BUILD_DIR)/obj
SRC=$(wildcard *.cpp)
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
