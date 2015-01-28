.PHONY: all clean
SERVER_DIR := .
SERVER_SRCS := server.c

CLIENT_DIR := .
CLIENT_SRCS := client.c

C_DIR := ../common
C_SRCS := my-pjlib-utils.c

DUPSOCK_DIR := ../duplex-socket
DUPSOCK_SRCS := duplex-socket.c

UDPS_DIR := .
UDPS_SRCS := udp-server.c

CCQUEUE_DIR := ../concurrent_queue
CCQUEUE_SRCS := queue.c qepool.c

OPOOL_DIR := ../object-pool
OPOOL_SRCS := object-pool.c

CFLAGS := -O0 $(shell pkg-config --cflags libpjproject) -I$(C_DIR)/include -I$(DUPSOCK_DIR)/include -I$(UDPS_DIR)/include -g
CFLAGS += -I$(CCQUEUE_DIR)/include
CFLAGS += -I$(OPOOL_DIR)/include 

#LIBS := $(shell pkg-config --libs libpjproject) -g
#LIBS := -L/opt/pjsip/lib -L/opt/local/lib -lstdc++ -lpjlib-util-x86_64-apple-darwin12.5.0 -lpj-x86_64-apple-darwin12.5.0 -lm -lpthread -framework CoreServices -framework QuartzCore
LIBS := -L/opt/pjsip/lib -L/opt/local/lib -lpjlib-util-x86_64-apple-darwin12.5.0 -lpj-x86_64-apple-darwin12.5.0 -lm -lpthread

CLIENT := client
SERVER := server
APP := $(CLIENT) $(SERVER)

DICOM_NANOPB := $(shell cd ../../nanopb;pwd)
#DICOM_PBASE_DIR := $(shell cd ../exchange-formats;pwd)
#PROTOS := seige.proto

all: $(APP)

include ../exchange-formats/proto-base.mk

CFLAGS += -I$(PROTO_CFLAGS)

$(SERVER): $(SERVER_SRCS:.c=.o) $(C_SRCS:.c=.o) $(DUPSOCK_SRCS:.c=.o) $(UDPS_SRCS:.c=.o) $(CCQUEUE_SRCS:.c=.o) $(OPOOL_SRCS:.c=.o) $(DICOM_PROTO_OBJS)
	gcc -o $@ $^ $(LIBS);
	strip $@

$(CLIENT): $(CLIENT_SRCS:.c=.o) $(C_SRCS:.c=.o) $(DUPSOCK_SRCS:.c=.o) $(UDPS_SRCS:.c=.o) $(CCQUEUE_SRCS:.c=.o) $(OPOOL_SRCS:.c=.o) $(DICOM_PROTO_OBJS)
	gcc -o $@ $^ $(LIBS)
	strip $@

$(CLIENT_SRCS:.c=.o) : %.o : $(CLIENT_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(SERVER_SRCS:.c=.o) : %.o : $(SERVER_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(C_SRCS:.c=.o) : %.o : $(C_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(DUPSOCK_SRCS:.c=.o) : %.o : $(DUPSOCK_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(UDPS_SRCS:.c=.o) : %.o : $(UDPS_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(CCQUEUE_SRCS:.c=.o) : %.o : $(CCQUEUE_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(OPOOL_SRCS:.c=.o) : %.o : $(OPOOL_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean: nano-clean
	rm -fr $(APP) *.o

#full-clean: clean proto-src-clean
