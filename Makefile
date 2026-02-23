# Nom du programme
TARGET = batterie

# Compilateur
CC = gcc

# Flags SDL
SDL_CFLAGS  = $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image)
SDL_LIBS    = $(shell pkg-config --libs   sdl2 SDL2_ttf SDL2_image)

CFLAGS  = -Wall -Wextra -std=c11 $(SDL_CFLAGS)
LDFLAGS = $(SDL_LIBS)

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Fichiers sources
SRC = $(wildcard $(SRC_DIR)/*.c)

# Remplace src/xxx.c → obj/xxx.o
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Exécutable final
EXEC = $(BIN_DIR)/$(TARGET)

# Règle principale
all: $(EXEC)

# Link final
$(EXEC): $(OBJ) | $(BIN_DIR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compilation .c → obj/.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Création automatique des dossiers si absents
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild complet
re: clean all

.PHONY: all clean re