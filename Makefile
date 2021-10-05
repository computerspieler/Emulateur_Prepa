SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%,bin/%.o,$(SRCS))
DEPS=$(patsubst src/%,bin/%.d,$(SRCS))

CC=gcc
CFLAGS=-c -g -Isrc/ -Wall -Wextra -DDEBUG
LDFLAGS=-g

all: program

clean:
	rm -rf bin

program: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

bin/%.c.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<

bin/%.c.d: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -M -MT $(patsubst %.d, %.o, $@) -o $@ $<

-include $(DEPS)
