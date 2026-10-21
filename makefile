CFLAGS := -g -O0 -march=native
SOURCE := ./rcipher.c

all: rcipher
	$(MAKE) -C . rcipher

rcipher: $(SOURCE)
	cc $(CFLAGS) -o $@ $(SOURCE)

run:
	./rcipher

clean:
	rm -rf ./rcipher

.PHONY: all clean run
