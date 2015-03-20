.PHONY: all clean
C_DIR := ../common
C_SRCS := my-pjlib-utils.c ansi-utils.c

MAIN_DIR := .
MAIN_SRCS := main.c

USB_DIR := ../usb
USB_SRCS := my-usb-utils.c

APP := test-usb

C_FLAGS := -I$(C_DIR)/include -I$(USB_DIR)/include $(shell pkg-config --cflags libpjproject)
LIBS := $(shell pkg-config --libs libpjproject)
all: $(APP)

$(APP) : $(C_SRCS:.c=.o) $(MAIN_SRCS:.c=.o) $(USB_SRCS:.c=.o)
	$(CC) -o $@ $^ $(LIBS)

$(C_SRCS:.c=.o) : %.o : $(C_DIR)/src/%.c
	$(CC) -o $@ -c $< $(C_FLAGS)

$(MAIN_SRCS:.c=.o) : %.o : $(MAIN_DIR)/src/%.c
	$(CC) -o $@  -c $< $(C_FLAGS)

$(USB_SRCS:.c=.o) : %.o : $(USB_DIR)/src/%.c
	$(CC) -o $@  -c $< $(C_FLAGS)

clean:
	rm -fr *.o $(APP)
