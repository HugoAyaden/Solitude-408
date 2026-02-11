# Nom du programme
TARGET = batterie

# Compilateur
CC = gcc

# Flags
SDL_CFLAGS  = $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image)
SDL_LIBS    = $(shell pkg-config --libs   sdl2 SDL2_ttf SDL2_image)

CFLAGS  = -Wall -Wextra -std=c11 $(SDL_CFLAGS)
LDFLAGS = $(SDL_LIBS)

# Dossiers
SRC_DIR = test

# Fichiers sources
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Règle principale
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compilation des .c en .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Nettoyage
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

# Rebuild complet
re: clean all

.PHONY: all clean re
