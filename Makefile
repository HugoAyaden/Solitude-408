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
MKDIR = mkdir -p $(1)
RM = rm -rf $(1)

ifeq ($(OS),Windows_NT)
    TARGET_EXT := .exe
    EXTRA_LIBS := -lssp
else
    TARGET_EXT :=
    EXTRA_LIBS :=
endif

# --- SDL CONFIGURATION  ---
INCLUDES := -I./lib $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image SDL2_mixer)
LIBS := $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image SDL2_mixer) $(EXTRA_LIBS)
CUNIT_CFLAGS := $(shell pkg-config --cflags cunit 2>/dev/null)
CUNIT_LIBS := $(shell pkg-config --libs cunit 2>/dev/null) -lcunit

# --- PROJECT STRUCTURE ---
SRCDIRS := src
SRCS := $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))
TEST_BUTTONS_SRC := tests/test_buttons.c
TEST_LIGHTS_SRC := tests/test_buttons_light.c
TEST_LINK_SRCS := $(filter-out src/main.c,$(SRCS))

OBJDIR := obj
BINDIR := bin
TARGET := $(BINDIR)/Solitude408$(TARGET_EXT)
TEST_TARGET := $(BINDIR)/test_buttons$(TARGET_EXT)
TEST_LIGHTS := $(BINDIR)/test_buttons_light$(TARGET_EXT)
TEST_TARGETS := $(TEST_TARGET) $(TEST_LIGHTS)

OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(notdir $(SRCS))))

.PHONY: all clean dirs run test

all: dirs $(TARGET)

test: $(TEST_TARGETS)

$(TEST_TARGET): dirs $(TEST_BUTTONS_SRC) $(TEST_LINK_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(CUNIT_CFLAGS) -o $@ $(TEST_BUTTONS_SRC) $(TEST_LINK_SRCS) $(LIBS) $(CUNIT_LIBS)

$(TEST_LIGHTS): dirs $(TEST_LIGHTS_SRC) $(TEST_LINK_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(CUNIT_CFLAGS) -o $@ $(TEST_LIGHTS_SRC) $(TEST_LINK_SRCS) $(LIBS) $(CUNIT_LIBS)

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
