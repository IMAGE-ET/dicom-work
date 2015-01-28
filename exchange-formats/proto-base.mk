#Need $(DICOM_NANOPB) defined

NANOPB_SRC := pb_encode.c pb_decode.c pb_common.c
DICOM_PROTO_OBJS += $(NANOPB_SRC:.c=.o) 
PROTO_CFLAGS += -I$(DICOM_NANOPB)

$(NANOPB_SRC:.c=.o): %.o: $(DICOM_NANOPB)/%.c
	gcc -o $@ -c $< $(PROTO_CFLAGS)

nano-clean:
	rm -fr $(NANOPB_SRC:.c=.o)
