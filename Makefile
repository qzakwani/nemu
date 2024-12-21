CC = gcc

DEV_CFLAGS = -Wall -Wextra -pedantic -g -I./include
BUILD_CFLAGS = -Wall -Wextra -pedantic -O2 -march=x86-64 -I./include

SRC_DIR = src
DEV_BUILD_DIR = build/dev
BUILD_BUILD_DIR = build/release
DEV_OUT_DIR = out/dev
RELEASE_OUT_DIR = out/release
DEV_EXEC = $(DEV_OUT_DIR)/nemu
BUILD_EXEC = $(RELEASE_OUT_DIR)/nemu

DEV_SOURCES = $(wildcard $(SRC_DIR)/*.c)
BUILD_SOURCES = $(wildcard $(SRC_DIR)/*.c)
DEV_OBJECTS = $(DEV_SOURCES:$(SRC_DIR)/%.c=$(DEV_BUILD_DIR)/%.o)
BUILD_OBJECTS = $(BUILD_SOURCES:$(SRC_DIR)/%.c=$(BUILD_BUILD_DIR)/%.o)

.PHONY: build clean run run2


run: $(DEV_EXEC)
	./$(DEV_EXEC)

run2: $(DEV_EXEC)
	./$(DEV_EXEC) -


$(DEV_EXEC): $(DEV_OBJECTS)
	@mkdir -p $(DEV_OUT_DIR)
	$(CC) $(DEV_OBJECTS) -o $(DEV_EXEC) -L./lib -lraylib -lm
	@echo "Development build successful: $(DEV_EXEC)"

$(DEV_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(DEV_BUILD_DIR)
	$(CC) $(DEV_CFLAGS) -c $< -o $@


build: $(BUILD_EXEC)

$(BUILD_EXEC): $(BUILD_OBJECTS)
	@mkdir -p $(RELEASE_OUT_DIR)
	$(CC) $(BUILD_OBJECTS) -o $(BUILD_EXEC) -L./lib -lraylib -lm
	@echo "Build for deployment successful: $(BUILD_EXEC)"

$(BUILD_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_BUILD_DIR)
	$(CC) $(BUILD_CFLAGS) -c $< -o $@


clean:
	rm -rf $(DEV_BUILD_DIR) $(BUILD_BUILD_DIR) $(DEV_OUT_DIR) $(RELEASE_OUT_DIR)
	@echo "Clean successful."
