EXEC = exec 
SRC_DIR = ./src
INCLUDE_DIR = ./include
BUILD_DIR = ./build

CC = g++
INCLUDES = $(addprefix -I, $(INCLUDE_DIR))
CFLAGS += -c -O2 -Wall -MMD -std=c++11 $(INCLUDES)

SRCS = $(shell find ./src -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
-include $(OBJS:.o=.d)

.PHONY:build run clean

build: $(OBJS)
	@$(CC) $(OBJS) -o $(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "+ CC $<"
	@mkdir -p $(@D)	
	@$(CC) $(CFLAGS) $< -o $@

run: build
	@./$(EXEC)

clean:
	@rm -rf $(BUILD_DIR)
	@rm $(EXEC)
