
PROG := bobdec
CONF := RELEASE

FLAGS := -I.

ifeq ($(CONF),RELEASE)
FLAGS += -Oz -fwhole-program
FLAGS += -falign-functions -falign-jumps -falign-labels
FLAGS += -falign-loops -freorder-blocks-algorithm=stc
FLAGS += -fno-unwind-tables -fno-asynchronous-unwind-tables
FLAGS += -fno-stack-protector -fno-ident -fno-exceptions
FLAGS += -fPIE -fno-plt -fno-pic -fPIE
FLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections
FLAGS += -z noseparate-code
FLAGS += -D RELEASE
else
FLAGS += -Og -ggdb
FLAGS += -D DEBUG
endif

CFLAGS := -std=c99 -Wall -Wextra
LDFLAGS :=
ifeq ($(CONF),RELEASE)
LDFLAGS += -s -Wl,--strip-all
endif

RSECs := .comment .gnu.hash .note.gnu.property .note.gnu.build-id .note.ABI-tag .gnu.version
RSECs += .eh_frame_hdr .eh_frame

SRCs := $(shell find . -name '*.c')
OBJs := $(addprefix tmp/,$(SRCs:.c=.o))
SRCs += $(wildcard *.h)

all: $(OBJs)
	mkdir -p bin
	gcc $(FLAGS) $(LDFLAGS) $^ -o bin/$(PROG)
	strip -s $(addprefix -R ,$(RSECs)) bin/$(PROG)

tmp/%.o: %.c
	mkdir -p $(@D)
	gcc $(FLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf tmp
	rm -f enc/*.c enc/*.h

.PHONY: clean all