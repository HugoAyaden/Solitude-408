CC=gcc

# Paths based on your custom installation
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

# Includes and Linking
INCLUDES=-I${SDLINC_DIR}
LIBS=-L${SDLLIB_DIR} -Wl,-rpath,${SDLLIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

# Source files across your folders
SRCS=main.c \
     Menu/menu.c \
     Settings/settings.c \
     Transition/transition.c

PROG=Solitude408

all: $(PROG)

$(PROG): $(SRCS)
	$(CC) $(SRCS) -o $(PROG) $(INCLUDES) $(LIBS)

clean:
	rm -f $(PROG)
	rm -f *.o