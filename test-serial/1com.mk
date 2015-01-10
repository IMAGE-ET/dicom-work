$(APP): $(MAIN_SRCS:.c=.o) $(C_SRCS:.c=.o) $(SERIAL_SRCS:.c=.o)
	@echo [LINK]: $@
	@$(CC) -o $@ $^ $(LIBS)

$(MAIN_SRCS:.c=.o) : %.o : $(MAIN_DIR)/src/%.c
	@echo [CC]: $@
	@$(CC) -o $@ -c $< $(CFLAGS)

$(SERIAL_SRCS:.c=.o) : %.o : $(SERIAL_DIR)/src/%.c
	@echo [CC]: $@
	@$(CC) -o $@ -c $< $(CFLAGS)

$(C_SRCS:.c=.o) : %.o : $(C_DIR)/src/%.c
	@echo [CC]: $@
	@$(CC) -o $@ -c $< $(CFLAGS)
