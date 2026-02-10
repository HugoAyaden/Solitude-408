CC=gcc
CFLAGS=-Wall -Wextra -g

# SDL2 configuration
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

# Include paths
INCLUDES=-I${SDLINC_DIR} -I./lib

# Libraries
LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image

# Output
PROG=fich1
SRCDIR=.
OBJDIR=obj
BINDIR=bin

# Source files
SOURCES=$(SRCDIR)/fich1.c
OBJECTS=$(OBJDIR)/fich1.o

# Targets
.PHONY: all clean

all: $(BINDIR)/$(PROG)

$(BINDIR)/$(PROG): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -f $(BINDIR)/$(PROG)

run: $(BINDIR)/$(PROG)
	./$(BINDIR)/$(PROG)
