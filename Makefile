ARM_CC ?= arm-linux-gnueabihf-gcc
ARM_CFLAGS = -g -Wall -Wextra -Ofast -mfpu=neon
EXEC = pipeline

all:$(EXEC)

pipeline: pipeline.c
	$(ARM_CC) $(ARM_CFLAGS) -o $@ $<

clean:
	$(RM) pipeline
