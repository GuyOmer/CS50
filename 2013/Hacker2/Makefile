#
# Makefile
#
# Computer Science 50
# Problem Set 6
#


# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -ggdb -O0 -Qunused-arguments -std=c99 -Wall -Werror

# crack
CRACK = crack
CRACK_SRCS = crack.c
CRACK_OBJS = $(CRACK_SRCS:.c=.o)

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = -lm -lcs50 -lcrypt

# target
$(CRACK): $(CRACK_OBJS)
	$(CC) $(CFLAGS) -o $@ $(CRACK_OBJS) $(LIBS)

# housekeeping
clean:
	rm -f core $(DUMP) *.o
	rm -f core $(PUFF) *.o
