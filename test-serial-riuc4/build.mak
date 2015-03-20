.PHONY: all clean

C_DIR := ../common
C_SRCS := my-pjlib-utils.c

SERIAL_DIR := ../serial
SERIAL_SRCS := riuc4_uart.c serial_utils.c

MAIN_DIR := .
MAIN_SRCS := main.c

APP := myapp-riuc4

CFLAGS := -g $(shell pkg-config --cflags libpjproject) -I $(C_DIR)/include -I $(MAIN_DIR)/include -I $(SERIAL_DIR)/include
LIBS := $(shell pkg-config --libs libpjproject)

all: $(APP)

$(APP): $(MAIN_SRCS:.c=.o) $(C_SRCS:.c=.o) $(SERIAL_SRCS:.c=.o)
	@echo [LINK]: $@
	@$(CC) -o $@ $^ $(LIBS)

$(MAIN_SRCS:.c=.o) : %.o : $(MAIN_DIR)/src/%.c
	@echo [CC]: $@
	@$(CC) -o $@ -c $< $(CFLAGS)

$(SERIAL_SRCS:.c=.o) : %.o : $(SERIAL_DIR)/src/%.c
	@echo [CC]: $@
	@$(CC) -o $@ -c $< $(CFLAGS)

$(C_SRCS:.c=.o) : %.o : $(C_DIR)/src/%.c
	@echo [CC]: $@
	@$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -fr *.o $(APP)
