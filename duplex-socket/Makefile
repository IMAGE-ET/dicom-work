.PHONY: all clean

C_DIR := ../common
C_SRCS := my-pjlib-utils.c my-pjmedia-utils.c ini.c dicom-config.c

DUPSOCK_DIR := .
DUPSOCK_SRCS := duplex-socket.c

MAIN_DIR := .
MAIN_SRCS := main.c

CFLAGS := $(shell pkg-config --cflags libpjproject) -I$(C_DIR)/include -I$(DUPSOCK_DIR)/include

LIBS := $(shell pkg-config --libs libpjproject)

APP := test-dupsock
all: $(APP)

$(APP): $(C_SRCS:.c=.o) $(DUPSOCK_SRCS:.c=.o) $(MAIN_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(C_SRCS:.c=.o): %.o: $(C_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(DUPSOCK_SRCS:.c=.o): %.o: $(DUPSOCK_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(MAIN_SRCS:.c=.o): %.o: $(MAIN_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -fr *.o $(APP)
