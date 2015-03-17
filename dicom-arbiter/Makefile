.PHONY: all clean full-clean

DICOM_NANOPB := $(shell cd ../../nanopb;pwd)
DICOM_PBASE_DIR := $(shell cd ../exchange-formats;pwd)
PROTOS := seige.proto

APP := arbiter
all: $(APP)
include $(DICOM_PBASE_DIR)/proto-base.mk
include $(DICOM_PBASE_DIR)/proto.mk
CFLAGS := -I$(DICOM_NANOPB) -I$(PROTO_DIR)

M_DIR := .
M_SRCS := arbiter.c

C_DIR := ../common
C_SRCS := my-pjlib-utils.c

Q_DIR := ../concurrent_queue
Q_SRCS := qepool.c queue.c

O_DIR := ../object-pool
O_SRCS := object-pool.c

DUPSOCK_DIR := ../duplex-socket
DUPSOCK_SRCS := duplex-socket.c

UDPS_DIR := ../udp-server
UDPS_SRCS := udp-server.c

CFLAGS += -I$(C_DIR)/include -I$(DUPSOCK_DIR)/include -I$(UDPS_DIR)/include -I$(Q_DIR)/include -I$(O_DIR)/include
CFLAGS += $(shell pkg-config --cflags libpjproject)

LIBS := $(shell pkg-config --libs libpjproject)

$(APP): $(DICOM_PROTO_OBJS) $(M_SRCS:.c=.o) $(C_SRCS:.c=.o) $(DUPSOCK_SRCS:.c=.o) $(UDPS_SRCS:.c=.o) $(Q_SRCS:.c=.o) $(O_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(M_SRCS:.c=.o) : %.o : $(M_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)

$(C_SRCS:.c=.o) : %.o : $(C_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)

$(Q_SRCS:.c=.o) : %.o : $(Q_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)

$(O_SRCS:.c=.o) : %.o : $(O_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)

$(DUPSOCK_SRCS:.c=.o) : %.o : $(DUPSOCK_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)

$(UDPS_SRCS:.c=.o) : %.o : $(UDPS_DIR)/src/%.c
	gcc -c -o $@ $< $(CFLAGS)

clean: nano-clean proto-clean
	rm -fr $(M_SRCS:.c=.o) $(C_SRCS:.c=.o) $(DUPSOCK_SRCS:.c=.o) $(UDPS_SRCS:.c=.o) $(APP)

full-clean: clean proto-src-clean
