
CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

# Added -lm (math library) just in case, and fixed the naming
LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lm
INCLUDES=-I${SDLINC_DIR} 

PROG=sdl_test

all: $(PROG)

$(PROG): menu.c
	${CC} menu.c -o ${PROG} ${INCLUDES} ${LIBS}

clean: 
	rm -f ${PROG}
	rm -f *.o