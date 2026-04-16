CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lcunit

# Paths relative to tests/
TEST_DIR = .
SRC_DIR = ../src
LIB_DIR = ../lib

TARGET = test_buttons
SRC = $(TEST_DIR)/test_buttons.c $(SRC_DIR)/game_core.c $(SRC_DIR)/constantes.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I$(SRC_DIR) -o $@ $(SRC) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)