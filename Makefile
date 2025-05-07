CC = gcc

CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG -I$(SRC_DIR) -I$(GAME_DIR) -I$(IO_DIR) -I$(HANDLER_DIR) -fsanitize=address
LIBS = -lncursesw

SRC_DIR = src
GAME_DIR = $(SRC_DIR)/game
IO_DIR = $(SRC_DIR)/io
HANDLER_DIR = $(SRC_DIR)/handler

OBJ = $(SRC_DIR)/main.o $(GAME_DIR)/game.o $(IO_DIR)/io.o $(HANDLER_DIR)/handler.o

BIN_DIR = build
TARGET = $(BIN_DIR)/battleship

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(GAME_DIR)%.o: $(GAME_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(IO_DIR)%.o: $(IO_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(HANDLER_DIR)%.o: $(HANDLER_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) 

rebuild: clean $(TARGET)
