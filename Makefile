
PROG := bobdec
CONF := DEBUG

FLAGS := -I. -liconv

ifeq (CONF, RELEASE)
FLAGS += -Oz -fwhole-program
FLAGS += -D RELEASE
else
FLAGS += -Og -ggdb
FLAGS += -D DEBUG
endif

CFLAGS := -std=c99 -Wall -Wextra
LDFLAGS :=

SRCs := $(shell find . -name '*.c')
OBJs := $(addprefix tmp/,$(SRCs:.c=.o))
SRCs += $(wildcard *.h)

all: $(OBJs)
	mkdir -p bin
	gcc $(FLAGS) $(LDFLAGS) $^ -o bin/$(PROG)
	#strip -s -R .gnu.hash -R .note.gnu.property bin/$(PROG)

tmp/%.o: %.c
	mkdir -p $(@D)
	gcc $(FLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf tmp
	rm -f enc/*.c enc/*.h

.PHONY: clean all