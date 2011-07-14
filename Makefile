CC := gcc

#INCLUDECFLAGS := `pkg-config --cflags IL`
#INCLUDELIBFLAGS := -lm `pkg-config --libs IL` -I"."
#INCLUDEFLAGS := $(INCLUDECFLAGS) $(INCLUDELIBFLAGS)

INCLUDEFLAGS := -lm -lpthread -lgmp -D_POSIX_SOURCE #-I"/usr/include/i386-linux-gnu/"

CPU_ARCHITECTURE := core2

# Flags in common by all
CFLAGS := -std=c99 -Wall -Wextra -pedantic -pedantic-errors -Wfloat-equal -Wundef -Wshadow -Winit-self
# Flags for debugging builds
CDFLAGS := $(CFLAGS) -g -O0 -fstack-protector-all -Wstack-protector -Wstrict-overflow=4
# Flags for normal builds
CNFLAGS := $(CFLAGS) -mtune=$(CPU_ARCHITECTURE) -O3 -fno-stack-protector -Wstrict-overflow -Wswitch-default \
-Wunreachable-code -Winline -Winit-self

# flags for the HPC machine. It has an old GCC, and doesn't know all flags newer GCCs do.
CHPCFLAGS := -std=c99 -Wall -Wextra -pedantic -Wfloat-equal -Wundef -Wshadow -Winit-self \
-O3 -fno-stack-protector -Wswitch-default -Wunreachable-code -Winline -Winit-self

BINNAME := mandel

default: clean analyze
	@$(CC) $(CNFLAGS) $(INCLUDEFLAGS) *.c -o $(BINNAME)
debug: clean analyze
	@$(CC) -g $(CNFLAGS) $(INCLUDEFLAGS) *.c -o $(BINNAME)
clean:
	@$(RM) $(BINNAME)
	@$(RM) *.plist
hpc:
	@$(CC) $(CHPCFLAGS) $(INCLUDEFLAGS) *.c -o $(BINNAME)

# Clang Compiler
CLANG := clang
CLANGFLAGS := -std=c99 -march=$(CPU_ARCHITECTURE) -O2 -I"/usr/include/i386-linux-gnu/"
clang: clean analyze
	@$(CLANG) $(CLANGFLAGS) *.c $(INTFILE) -o engine
analyze:
	@$(CLANG) $(CLANGFLAGS) --analyze *.c $(INTFILE)

