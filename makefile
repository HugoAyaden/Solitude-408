###############################################################################
# Generic Makefile
# - builds all C sources found in src/, fichiers/, test/, test/Menu/
# - object files are placed in obj/
# - final executable is placed in bin/projet (change TARGET if you like)
###############################################################################

CC ?= gcc
CFLAGS ?= -Wall

# Add debug flags by setting DEBUG=1 when calling make (e.g. make DEBUG=1)
ifneq ($(DEBUG),)
CFLAGS += -g
else
CFLAGS += -O2
endif

# Optional SDL configuration (set SDL_DIR in environment or on make command line)
SDL_DIR ?= $(HOME)/SDL2
SDLLIB_DIR ?= $(SDL_DIR)/lib
SDLINC_DIR ?= $(SDL_DIR)/include
INCLUDES ?= -I./lib -I$(SDLINC_DIR)
LIBS ?= -L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image


SRCDIRS := src fichiers test
SRCS := $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))

OBJDIR := obj
BINDIR := bin
TARGET := $(BINDIR)/projet

OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(notdir $(SRCS))))

.PHONY: all clean dirs run

all: dirs $(TARGET)

dirs:
	mkdir -p $(OBJDIR) $(BINDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Create per-source object rules so each object depends on the exact source file.
# This lets make detect changes and rebuild the corresponding object.
define make_obj_rule
$(OBJDIR)/$(notdir $(1:.c=.o)): $(1)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(1) -o $$@
endef

$(foreach src,$(SRCS),$(eval $(call make_obj_rule,$(src))))

clean:
	rm -rf $(OBJDIR) $(BINDIR)/projet

run: $(TARGET)
	./$(TARGET)

print-info:
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"

###############################################################################
# Notes:
# - To build with debug symbols: make DEBUG=1
# - To enable SDL linking, adjust SDL_DIR or override INCLUDES/LIBS on the make
#   command line, e.g.:
#     make INCLUDES='-I/home/user/SDL2/include' LIBS='-L/home/user/SDL2/lib -lSDL2'
###############################################################################
