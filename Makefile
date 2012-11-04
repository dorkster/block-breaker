PROJNAME=block-breaker
SRCDIR=src
BUILDDIR=build
SOURCES=$(SRCDIR)/draw.c $(SRCDIR)/game.c $(SRCDIR)/sys.c $(SRCDIR)/main.c
OBJECTS=$(BUILDDIR)/draw.o $(BUILDDIR)/game.o $(BUILDDIR)/sys.o $(BUILDDIR)/main.o

CC=gcc
CFLAGS+=
LDFLAGS+=-lSDL -lSDL_gfx -lSDL_ttf
EXECUTABLE=$(PROJNAME)
all: build $(SOURCES) $(EXECUTABLE)

build:
	mkdir -p build/

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -Wall -O2 -mms-bitfields -std=c99 -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $< $ $(CFLAGS) -c -Wall -O2 -mms-bitfields -std=c99 -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
