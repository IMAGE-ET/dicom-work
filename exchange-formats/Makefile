.PHONY: all clean
PROTOS := ptt-session.proto
DICOM_NANOPB := $(shell cd ../../nanopb;pwd)
DICOM_PBASE_DIR := $(shell pwd)

all: main

#include dicom-proto.mk
include proto-base.mk
include proto.mk

SRC_DIR := src
SRC := test.c

C_DIR := ../common
C_SRCS := my-pjlib-utils.c

CFLAGS := $(shell pkg-config --cflags libpjproject)
CFLAGS += -I$(DICOM_NANOPB) -I$(PROTO_DIR) -Iinclude -I$(C_DIR)/include

LIBS := $(shell pkg-config --libs libpjproject)

main: $(PROTOS:.proto=.pb.o) $(NANOPB_SRC:.c=.o) $(SRC:.c=.o) $(C_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(SRC:.c=.o): %.o: $(SRC_DIR)/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(C_SRCS:.c=.o): %.o: $(C_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean: proto-clean nano-clean
	rm -fr $(C_SRCS:.c=.o) $(SRC:.c=.o) main

full-clean: clean proto-src-clean
