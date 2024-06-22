CC     = gcc
CFLAGS = -fuse-ld=mold -ggdb -Wpedantic -Wall -Wextra
IN     = main.c token.c
OUT    = dos_scm

default:
	$(CC) $(CFLAGS) $(IN) -o $(OUT)
