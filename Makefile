CC = clang
LD = $(CC)

CFLAGS = -Wall -pipe -Iinclude/
OFLAGS = 
LFLAGS =

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

DEBUG = no
PROFILE = no
OPTIMIZATION = -O3

ifeq ($(DEBUG), yes)
	CFLAGS += -g -DDEBUG
endif

ifeq ($(PROFILE), yes)
	CFLAGS += -g -pg -DPROFILE
endif

CFLAGS += $(OPTIMIZATION)

all: netchess

netchess: $(OBJECTS)
	$(LD) $(LFLAGS) $(OBJECTS) -o netchess

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf netchess  gmon.out *.save *.o core* vgcore*

rebuild: clean all

.PHONY : clean
.SILENT : clean
.NOTPARALELL : clean
