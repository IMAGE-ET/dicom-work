CC=gcc

#LDFLAGS=-L/tmp/pjsip-pc/lib
CFLAGS=-I include -g
LIBS=-lpthread

SRCDIR=src
OBJDIR=build
APPDIR=test

TEST_SRCS=test-queue.c

APP=test-queue

LIB_NAME=conqueue
#LIB_EXT=so
LIB_EXT=a
LIB_FILE=$(OBJDIR)/lib$(LIB_NAME).$(LIB_EXT)

LIB_SRCS=queue.c
LIB_OBJS=$(addprefix $(OBJDIR)/, $(LIB_SRCS:.c=.o))

TEST_OBJS=$(addprefix $(OBJDIR)/, $(TEST_SRCS:.c=.o))

.PHONY: all test clean

all: $(OBJDIR) $(LIB_FILE) test

$(OBJDIR):
	mkdir $@

test: $(APP)

$(LIB_FILE): $(LIB_OBJS)
#	$(CC) -shared -o $@ $(LIB_OBJS) $(LDFLAGS) $(LIBS)
	ar rcs $@ $^

$(APP): $(LIB_FILE) $(TEST_OBJS)
	$(CC) -o $(OBJDIR)/$(APP) $(TEST_OBJS) -L $(OBJDIR) -l$(LIB_NAME) $(LDFLAGS) $(LIBS)

$(LIB_OBJS) : $(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(TEST_OBJS) : $(OBJDIR)/%.o: $(APPDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -fr $(OBJDIR)
