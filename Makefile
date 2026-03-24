PROJ=DS2NetFix

CC=x86_64-w64-mingw32-gcc
CFLAGS=-Wall -s -shared -Iminhook/include

$(PROJ).asi: dllmain.c mem.c minhook/src/*.c minhook/src/hde/*.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(PROJ).asi
