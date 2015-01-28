.PHONY: all clean
APP := test-opool

C_DIR := ../common
C_SRCS := my-pjlib-utils.c

OPOOL_DIR := .
OPOOL_SRCS := object-pool.c

MAIN_DIR := .
MAIN_SRCS := main.c

LIBS := $(shell pkg-config libpjproject --libs)

CFLAGS := $(shell pkg-config libpjproject --cflags) -I$(C_DIR)/include -I$(OPOOL_DIR)/include

all: $(APP)

$(APP): $(C_SRCS:.c=.o) $(OPOOL_SRCS:.c=.o) $(MAIN_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(C_SRCS:.c=.o): %.o: $(C_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(MAIN_SRCS:.c=.o): %.o: $(MAIN_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(OPOOL_SRCS:.c=.o): %.o: $(OPOOL_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -fr *.o $(APP)
