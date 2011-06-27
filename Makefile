CC := gcc

INCLUDECFLAGS := `pkg-config --cflags sdl`
INCLUDELIBFLAGS := -lm `pkg-config --libs sdl` -I"."
INCLUDEFLAGS := $(INCLUDECFLAGS) $(INCLUDELIBFLAGS)

CPU_ARCHITECTURE := pentium-m

# Flags in common by all
CFLAGS := -std=c99 -Wall -Wextra -pedantic -pedantic-errors -Wfloat-equal -Wundef -Wshadow -Winit-self
# Flags for debugging builds
CDFLAGS := $(CFLAGS) -g -O0 -fstack-protector-all -Wstack-protector -Wstrict-overflow=4
# Flags for normal builds
CNFLAGS := $(CFLAGS) -mtune=$(CPU_ARCHITECTURE) -O3 -fno-stack-protector -Wstrict-overflow -Wswitch-default \
-Wunreachable-code -Winline -Winit-self

BINNAME := mandel

default: clean analyze
	@$(CC) $(CNFLAGS) $(INCLUDEFLAGS) *.c -o $(BINNAME)
clean:
	@$(RM) $(BINNAME)
	@$(RM) *.plist

# Clang Compiler
CLANG := clang
CLANGFLAGS := -std=c99 -march=$(CPU_ARCHITECTURE) -O2
clang: clean analyze
	@$(CLANG) $(CLANGFLAGS) $(INCLUDEFLAGS) *.c $(INTFILE) -o engine
analyze:
	@$(CLANG) $(CLANGFLAGS) $(INCLUDECFLAGS) --analyze *.c $(INTFILE)

