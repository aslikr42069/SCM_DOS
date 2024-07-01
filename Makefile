CC     = gcc
CFLAGS = -fuse-ld=mold -ggdb -Wpedantic -Wall -Wextra
IN     = *.c
OUT    = dos_scm

default:
	$(CC) $(CFLAGS) $(IN) -o $(OUT)
