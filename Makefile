# t4 - simple dmenu
#
.POSIX:

include config.mk

SRC = t4.c
OBJ = $(SRC:.c=.o)

all: options t4

options:
	@echo t4 build options:
	@echo "CFLAGS   = $(T4_CFLAGS)"
	@echo "LDFLAGS  = $(T4_LDFLAGS)"
	@echo "CC       = $(CC)"

.c.o:
	@echo CC -c $<
	@$(CC) $(T4_CFLAGS) -c $<

$(OBJ): config.mk

t4: $(OBJ)
	@echo CC -o $@
	@$(CC) $(T4_CFLAGS) -o $@ $(OBJ) $(T4_LDFLAGS)

clean:
	@echo cleaning
	@rm -f $(NAME) $(OBJ)

install: all
	@echo installing executable file to $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp -f $(NAME) $(DESTDIR)$(PREFIX)/bin
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/$(NAME)
	@echo installing  $(DESTDIR)$(SHAREDIR)/$(NAME).css
	@mkdir -p $(DESTDIR)$(DATAPREFIX)/$(NAME)
	@cp -f $(NAME).css $(DESTDIR)$(DATAPREFIX)/$(NAME)/
	@chmod 644 $(DESTDIR)$(DATAPREFIX)/$(NAME)/$(NAME).css

uninstall:
	@echo removing executable file from $(DESTDIR)$(PREFIX)/bin
	@rm -f $(DESTDIR)$(PREFIX)/bin/$(NAME)
	@echo removing file style from $(DESTDIR)$(DATAPREFIX)/$(NAME)
	@rm -f $(DESTDIR)$(DATAPREFIX)/$(NAME)/$(NAME).css

.PHONY: all options clean dist install uninstall
