CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -g -I./include  

SRC_DIR = src
BUILD_DIR = build
OUT_DIR = out
EXEC = $(OUT_DIR)/nemu

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) -L./lib -lraylib -lm -lpthread -ldl -lrt -lX11
	@echo "Build successful."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: all clean run

all: $(EXEC)

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

run: $(EXEC)
	./$(EXEC)

run2: $(EXEC)
	./$(EXEC) -