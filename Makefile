#
# Makefile - Rules for building the program.
# 	Written by long.luo <uniqueluolong@gmail.com>
#	
#	History:
#		long.luo, 12/11/2012, created it.
#		long.luo, 13/11/2012, modified it.
#		long.luo, 15/01/2013, refactored the code.
#


# The compiler to be used.
ifndef COMPILER
COMPILER=gcc
endif

# Definitions for using GCC.
ifeq (${COMPILER}, gcc)

# The command for calling the compiler.
CC=gcc

# The flags passed to the compiler.
CFLAGS :=	-Wall \
			-Os  \
			-c

# The command for calling the linker.
LD=ld

# The Linker flags passed to the linker.
LDFLAGS := --gc-sections

# The PHONY targets.	
.PHONY: all clean

# The default rule, which causes the Application to be built.
all: tSH

# The rule to create the target directory.
${COMPILER}:
	mkdir ${COMPILER}

# The rule for building the object file from each C source file.
%.o : %.c
	${CC} ${CFLAGS} -D${COMPILER} -o $@ $<

# The objects.
OBJS =	TinyShell.o	\ 
	cmdline.o	\
	commands/cmd_ls.o	\
	commands/cmd_help.o	\
	commands/cmd_version.o

		

# The final executable file.
exec=tSH
	
# The rule for building the application.
tSH: ${OBJS}
	@echo "Done building object files"
	@echo
	$(CC) -o $@ $?
	@echo "Done"

# The rule to clean out all the build products.
clean:
	@echo "Cleaning object files..."
	rm -f ${wildcard *.o} ${wildcard commands/*.o} ${exec} 
	@echo "Done"
	
endif
