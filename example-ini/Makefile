.PHONY: all clean

APP:=oiu

MAIN_DIR := .
MAIN_SRCS := oiu_config.c main.c login.c

COMMON_DIR := ../common
COMMON_SRCS := ini.c

LIBS :=
CFLAGS := -g -I$(COMMON_DIR)/include -I$(MAIN_DIR)/include -Wall

all: $(APP)

$(APP): $(MAIN_SRCS:.c=.o) $(COMMON_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(COMMON_SRCS:.c=.o): %.o : $(COMMON_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(MAIN_SRCS:.c=.o): %.o : $(MAIN_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)


clean:
	rm -fr *.o $(APP)
