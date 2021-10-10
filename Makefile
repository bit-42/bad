OPTS = -Wall -Werror -leditline -lm
INCS = -Isrc/inc/ -I/usr/local/include
LIBS = -L/usr/local/lib

all:
	gcc $(INCS) $(LIBS) src/*.c -o bin/bad $(OPTS)
