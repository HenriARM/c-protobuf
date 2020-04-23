CC = gcc
CFLAGS = -Wall

OBJ = main.o pb_common.o pb_encode.o pb_decode.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
