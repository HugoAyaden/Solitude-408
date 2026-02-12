CC      := gcc
CFLAGS  := -Wall -Wextra -O2
# Directory Structure
SRCDIR  := src
LIBDIR  := lib
OBJDIR  := obj
BINDIR  := bin
TARGET  := $(BINDIR)/Solitude408

# SDL Configuration
SDL_DIR     ?= $(HOME)/SDL2
SDLINC_DIR  := $(SDL_DIR)/include
SDLLIB_DIR  := $(SDL_DIR)/lib

INCLUDES    := -I./$(LIBDIR) -I$(SDLINC_DIR)
LIBS        := -L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# Source files from src/ as per architecture requirements
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: all clean run

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: all
	./$(TARGET)