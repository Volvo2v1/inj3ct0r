SOURCE	= inj3ct0r.c
OUT	= inj3ct0r
CC	= cc

all:
	$(CC) $(SOURCE) -o $(OUT)

install:
	$(CC) $(SOURCE) -o $(OUT)
	cp $(OUT) /usr/bin/inj3ct0r

uninstall:
	rm /usr/bin/inj3ct0r

clean:
	rm $(OUT)
