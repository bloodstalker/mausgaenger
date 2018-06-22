TARGET=mausgaenger
CC=clang
CC?=clang
CC_FLAGS=
CC_EXTRA?=
CC_FLAGS+=$(CC_EXTRA)

SRCS=$(wildcard *.c)

.DEFAULT:all

.PHONY:all clean help

all:$(TARGET) $(TARGET).wasm

depend:.depend

.depend:$(SRCS)
	rm -rf .depend
	$(CC) -MM $(CC_FLAGS) $^ > ./.depend

-include ./.depend

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@ 

%.wasm:%.c
	./llvm.wasm.sh $<

$(TARGET): $(TARGET).o
	$(CC) $^ $(LD_FLAGS) -o $@

clean:
	rm -f *.o *~ $(TARGET) *.s *.wasm *.wast *.bc
	rm .depend

help:
	@echo "all is the default target"
	@echo "there is clean."
