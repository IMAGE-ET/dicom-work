.PHONY: all clean full-clean

DICOM_NANOPB := $(shell cd ../../nanopb;pwd)
DICOM_PBASE_DIR := $(shell cd ../exchange-formats;pwd)
PROTOS := ptt-session.proto

all: main
include ../exchange-formats/proto-base.mk
include ../exchange-formats/proto.mk

SRC_DIR := src
SRC := test.c
CFLAGS := -I$(DICOM_NANOPB) -I$(PROTO_DIR)

#main: $(PROTOS:.proto=.pb.o) $(NANOPB_SRC:.c=.o) $(SRC:.c=.o)
main: $(DICOM_PROTO_OBJS) $(SRC:.c=.o)
	gcc -o $@ $^

$(SRC:.c=.o): %.o: $(SRC_DIR)/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean: proto-clean nano-clean
	rm -fr $(SRC:.c=.o) main

full-clean: clean proto-src-clean
