ARM_CC ?= arm-linux-gnueabihf-gcc
ARM_CFLAGS = -g -Wall -Wextra -Ofast -mfpu=neon
EXEC = pipeline pipeline_flush

all:$(EXEC)

pipeline: pipeline.c
	$(ARM_CC) $(ARM_CFLAGS) -DNON_FLUSH -o $@ $<

pipeline_flush: pipeline.c
	$(ARM_CC) $(ARM_CFLAGS) -DFLUSH -o $@ $<

clean:
	$(RM) $(EXEC)
