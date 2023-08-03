BINARY = stp
INSTALLDIR = /usr/local/bin
CODEDIRS = src
INCDIRS = include
# TESTDIRS = tests
CC = gcc
OPT = -O0
DEPFLAGS = -MP -MD
INCLIBS = -lncurses
CFLAGS = -Wall -Wextra -g $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)
CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEPFILES = $(patsubst %.c, %.d, $(CFILES))

all: $(BINARY)


$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(INCLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

debug: all
	@./tmux.sh

install: $(BINARY)
	install -m 755 $(BINARY) $(INSTALLDIR)

uninstall:
	rm $(INSTALLDIR)/$(BINARY)

-include $(DEPFILES)
