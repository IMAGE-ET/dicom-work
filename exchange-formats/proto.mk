#Need $(DICOM_PBASE_DIR) defined
.PHONY: proto-gen proto-compile proto-clean
include $(DICOM_NANOPB)/extra/nanopb.mk

PROTO_DIR := proto
PROTO_CFLAGS += -I$(PROTO_DIR)

DICOM_PROTO_OBJS += $(PROTOS:.proto=.pb.o)

$(PROTO_DIR):
	mkdir -p $@

proto-gen: $(addprefix $(PROTO_DIR)/, $(PROTOS:.proto=.pb.c))

proto-compile: $(PROTOS:.proto=.pb.o)

$(PROTOS:.proto=.pb.o): %.pb.o: $(PROTO_DIR)/%.pb.c
	gcc -o $@ -c $< $(PROTO_CFLAGS)

$(addprefix $(PROTO_DIR)/, $(PROTOS:.proto=.pb.c)): $(PROTO_DIR)/%.pb.c : %.proto %.options $(PROTO_DIR) 
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=$(PROTO_DIR) $<

$(PROTOS): %.proto : $(DICOM_PBASE_DIR)/specs/%.proto
	cp $< $@

$(PROTOS:.proto=.options): %.options : $(DICOM_PBASE_DIR)/specs/%.options
	cp $< $@

proto-clean: 
	rm -fr $(PROTOS:.proto=.pb.o)
proto-src-clean: proto-clean
	rm -fr $(PROTO_DIR) $(PROTOS) $(PROTOS:.proto=.options)

