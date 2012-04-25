PROJNAME=block-breaker
SOURCES=src/draw.c src/game.c src/sys.c src/main.c

CC=gcc
CFLAGS+=
LDFLAGS+=-lSDL -lSDL_gfx -lSDL_ttf
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=$(PROJNAME)
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -Wall -O2 -mms-bitfields -std=c99 -o $@

.c.o:
	$(CC) $< $ $(CFLAGS) -c -Wall -O2 -mms-bitfields -std=c99 -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
