
INCLUDE_DIR = -I.

SOURCES = test_runtime_timer.c \
          timer.c

OBJECTS := $(notdir $(SOURCES:.c=.o))

all : $(OBJECTS)
	$(CC) $(OBJECTS) -o test_runtime -lpthread

%.o : %.c
	$(CC) -g $(CFLAGS) $(INCLUDE_DIR) -o $@ -c $<
