###############################################################################
# UNIVERSAL MAKEFILE (Windows/MSYS2, Linux, macOS)
###############################################################################

CC := gcc
CFLAGS := -Wall -fno-stack-protector -D_FORTIFY_SOURCE=0 -Wno-attributes
# Handle Debug vs Release
ifeq ($(DEBUG),1)
    CFLAGS += -g
else
    CFLAGS += -O2
endif

# --- OS DETECTION & COMMANDS ---
ifeq ($(OS),Windows_NT)
    # Windows/PowerShell/CMD
    MKDIR = if not exist $(subst /,\,$(1)) mkdir $(subst /,\,$(1))
    RM = if exist $(subst /,\,$(1)) rmdir /s /q $(subst /,\,$(1))
    TARGET_EXT := .exe
    EXTRA_LIBS := -lssp
else
    # Linux / macOS
    MKDIR = mkdir -p $(1)
    RM = rm -rf $(1)
    TARGET_EXT :=
    EXTRA_LIBS :=
endif

# --- SDL CONFIGURATION  ---
INCLUDES := -I./lib $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image SDL2_mixer)
LIBS := $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image SDL2_mixer) $(EXTRA_LIBS)

# --- PROJECT STRUCTURE ---
SRCDIRS := src
SRCS := $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))

OBJDIR := obj
BINDIR := bin
TARGET := $(BINDIR)/Solitude408$(TARGET_EXT)

OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(notdir $(SRCS))))

.PHONY: all clean dirs run

all: dirs $(TARGET)

dirs:
	@$(call MKDIR, $(OBJDIR))
	@$(call MKDIR, $(BINDIR))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

define make_obj_rule
$(OBJDIR)/$(notdir $(1:.c=.o)): $(1)
	@$(call MKDIR, $(OBJDIR))
	$(CC) $(CFLAGS) $(INCLUDES) -c $(1) -o $$@
endef

$(foreach src,$(SRCS),$(eval $(call make_obj_rule,$(src))))

clean:
	@$(call RM, $(OBJDIR))
	@$(call RM, $(BINDIR))

run: $(TARGET)
ifeq ($(OS),Windows_NT)
	@.\$(subst /,\,$(TARGET))
else
	@./$(TARGET)
endif
