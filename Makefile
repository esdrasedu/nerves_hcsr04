# Look for the EI library and header files
# For crosscompiled builds, ERL_EI_INCLUDE_DIR and ERL_EI_LIBDIR must be
# passed into the Makefile.
ifeq ($(ERL_EI_INCLUDE_DIR),)
  ERL_ROOT_DIR = $(shell erl -eval "io:format(\"~s~n\", [code:root_dir()])" -s init stop -noshell)
  ifeq ($(ERL_ROOT_DIR),)
     $(error Could not find the Erlang installation. Check to see that 'erl' is in your PATH)
  endif
  ERL_EI_INCLUDE_DIR = "$(ERL_ROOT_DIR)/usr/include"
  ERL_EI_LIBDIR = "$(ERL_ROOT_DIR)/usr/lib"
endif

# Set Erlang-specific compile and linker flags
ERL_CFLAGS ?= -I$(ERL_EI_INCLUDE_DIR)
ERL_LDFLAGS ?= -L$(ERL_EI_LIBDIR) -lerl_interface -lei

SRC =
LDFLAGS +=
CFLAGS ?= -O2 -Wall -Wextra -Wno-unused-parameter

ifeq ($(MIX_TARGET), rpi)
	SRC += $(wildcard src/Raspberry_Pi/*.c) src/_Raspberry_Pi_Driver.c
endif

ifeq ($(MIX_TARGET), rpi0)
	SRC += $(wildcard src/Raspberry_Pi/*.c) src/_Raspberry_Pi_Driver.c
endif

ifeq ($(MIX_TARGET), host)
	SRC += src/_Host_Driver.c
	CC ?= gcc
else
	CC ?= $(CROSSCOMPILER)-gcc
endif

OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: priv priv/nerves_hcsr04

%.o: %.c
	$(CC) -o $@ $^ -c $(ERL_CFLAGS) $(CFLAGS)

priv:
	mkdir -p priv

priv/nerves_hcsr04: $(OBJ)
	$(CC) $^ -o $@ $(ERL_LDFLAGS) $(LDFLAGS) -lpthread

clean:
	rm -f priv/nerves_hcsr04 src/*.o src/**/*.o
