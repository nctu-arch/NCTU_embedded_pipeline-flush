ARM_CC ?= arm-linux-gnueabihf-gcc
ARM_CFLAGS = -g -Wall -Wextra -O0 -mfpu=neon
EXEC = pipeline pipeline_flush

GIT_HOOKS := .git/hooks/applied
.PHONY: all
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

pipeline: pipeline.c
	$(ARM_CC) $(ARM_CFLAGS) -DNON_FLUSH -o $@ $<

pipeline_flush: pipeline.c
	$(ARM_CC) $(ARM_CFLAGS) -DFLUSH -o $@ $<

.PHONY: clean
clean:
	$(RM) $(EXEC)
