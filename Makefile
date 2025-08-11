# ==============================================================================
# Usage:
# make             # compile binary
# make debug       # compile debug
# make release     # compile release
# make run         # run debug
# make run-release # run release
# make clean       # remove ALL binaries and objects
# ==============================================================================

# Project name
EXECUTABLE := larry

# Directories
SRC_DIR     := src
BUILD_DIR   := bin
DEBUG_DIR   := $(BUILD_DIR)/debug
RELEASE_DIR := $(BUILD_DIR)/release

DEBUG_OBJ_DIR   := $(DEBUG_DIR)/obj
RELEASE_OBJ_DIR := $(RELEASE_DIR)/obj

INCLUDE_DIRS   := $(shell find ${SRC_DIR} -type d)
CFLAGS_INCLUDE := $(addprefix -I,$(INCLUDE_DIRS))

# Compiler
CC := gcc

# Flags
SDL_CFLAGS  := $(shell pkg-config --cflags sdl3)
SDL_LDFLAGS := $(shell pkg-config --libs sdl3)

CFLAGS_COMMON  := -Wall -Wextra -MMD -MP $(CFLAGS_INCLUDE) $(SDL_CFLAGS)
CFLAGS_DEBUG   := -g -O0 $(CFLAGS_COMMON) -fsanitize=address -fno-omit-frame-pointer
# CFLAGS_DEBUG   := -g -O0 $(CFLAGS_COMMON)
CFLAGS_RELEASE := -O2 $(CFLAGS_COMMON)

# Sources and Objects
SRCS := $(shell find $(SRC_DIR) -name '*.c')

DEBUG_BIN   := $(DEBUG_DIR)/$(EXECUTABLE)
RELEASE_BIN := $(RELEASE_DIR)/$(EXECUTABLE)

DEBUG_OBJS   := $(patsubst $(SRC_DIR)/%.c,$(DEBUG_OBJ_DIR)/%.o,$(SRCS))
RELEASE_OBJS := $(patsubst $(SRC_DIR)/%.c,$(RELEASE_OBJ_DIR)/%.o,$(SRCS))

DEBUG_DEPS   := $(DEBUG_OBJS:.o=.d)
RELEASE_DEPS := $(RELEASE_OBJS:.o=.d)

# Colors
BLUE  := \033[1;36m
GREEN := \033[1;32m
NC    := \033[0m # No Color

# ==============================================================================
# Targets
# ==============================================================================

.PHONY: all debug release run run-release clean
all: debug

debug: $(DEBUG_BIN)
	@echo "\n${GREEN}Build Successful!${NC}"

release: $(RELEASE_BIN)
	@echo "\n${GREEN}Build Successful!${NC}"

run: $(DEBUG_BIN)
	@echo "\n${GREEN}Running...${NC}"
	./$(DEBUG_BIN)

test: $(DEBUG_BIN)
	@echo "\n${GREEN}Testing...${NC}"
	./$(DEBUG_BIN) tests/test_script.txt

run-release: $(RELEASE_BIN)
	@echo "\n${GREEN}Running...${NC}"
	./$(RELEASE_BIN)

clean:
	@echo "${GREEN}Cleaning up...${NC}"
	rm -rf $(BUILD_DIR)

# ==============================================================================
# Build Rules
# ==============================================================================

$(DEBUG_BIN): $(DEBUG_OBJS)
	@echo "\n${GREEN}Linking ${BLUE}${@F}${NC}"
	$(CC) $(CFLAGS_DEBUG) $^ -o $@ $(SDL_LDFLAGS)

$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "${GREEN}Compiling ${BLUE}$<${NC}"
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

$(RELEASE_BIN): $(RELEASE_OBJS)
	@echo "${GREEN}Linking ${BLUE}${@F}${NC}"
	$(CC) $(CFLAGS_RELEASE) $^ -o $@ $(SDL_LDFLAGS)

$(RELEASE_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "${GREEN}Compiling $<${NC}"
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

# ==============================================================================
# Dependency Inclusion
# ==============================================================================

-include $(DEBUG_DEPS)
-include $(RELEASE_DEPS)

