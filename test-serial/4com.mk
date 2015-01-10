MYCFLAGS := -DRIUC4
$(APP4): $(MAIN_SRCS:.c=.o4) $(C_SRCS:.c=.o4) $(SERIAL_SRCS:.c=.o4)
	@echo [LINK]: $@
	$(CC) -o $@ $^ $(LIBS)

$(MAIN_SRCS:.c=.o4) : %.o4 : $(MAIN_DIR)/src/%.c
	@echo [CC]: $@
	$(CC) -o $@ -c $< $(CFLAGS) $(MYCFLAGS)

$(SERIAL_SRCS:.c=.o4) : %.o4 : $(SERIAL_DIR)/src/%.c
	@echo [CC]: $@
	$(CC) -o $@ -c $< $(CFLAGS) $(MYCFLAGS)

$(C_SRCS:.c=.o4) : %.o4 : $(C_DIR)/src/%.c
	@echo [CC]: $@
	$(CC) -o $@ -c $< $(CFLAGS) $(MYCFLAGS)

