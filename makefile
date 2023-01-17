CC = gcc
CFLAGS = -std=c99

virtual_ram: virtual_ram.c
	$(CC) $(CFLAGS) -o virtual_ram virtual_ram.c

run: virtual_ram
	./virtual_ram

clean:
	rm -f virtual_ram