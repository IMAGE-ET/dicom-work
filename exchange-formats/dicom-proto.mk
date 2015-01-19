.PHONY: proto-gen proto-compile proto-clean
include $(DICOM_NANOPB)/extra/nanopb.mk

SRC_DIR := src
PROTO_DIR := proto
PROTOS := ptt-session.proto
NANOPB_SRC := pb_encode.c pb_decode.c pb_common.c
PROTO_CFLAGS := -I$(DICOM_NANOPB) -I$(PROTO_DIR)

DICOM_PROTO_SRCS := $(PROTOS:.proto=.pb.o) $(NANOPB_SRC:.c=.o) 

$(PROTO_DIR):
	mkdir -p $@

proto-gen: $(addprefix $(PROTO_DIR)/, $(PROTOS:.proto=.pb.c))

proto-compile: $(NANOPB_SRC:.c=.o) $(PROTOS:.proto=.pb.o)

$(PROTOS:.proto=.pb.o): %.pb.o: $(PROTO_DIR)/%.pb.c
	gcc -o $@ -c $< $(PROTO_CFLAGS)

$(NANOPB_SRC:.c=.o): %.o: $(DICOM_NANOPB)/%.c
	gcc -o $@ -c $< $(PROTO_CFLAGS)

$(addprefix $(PROTO_DIR)/, $(PROTOS:.proto=.pb.c)): $(PROTO_DIR)/%.pb.c : %.proto %.options $(PROTO_DIR) 
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=$(PROTO_DIR) $<

$(PROTOS): %.proto : $(DICOM_PBASE_DIR)/specs/%.proto
	cp $< $@

$(PROTOS:.proto=.options): %.options : $(DICOM_PBASE_DIR)/specs/%.options
	cp $< $@

proto-clean:
	rm -fr $(NANOPB_SRC:.c=.o) $(PROTOS:.proto=.pb.o)
proto-src-clean: proto-clean
	rm -fr $(PROTO_DIR) $(PROTOS) $(PROTOS:.proto=.options)
