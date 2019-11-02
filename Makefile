# t4 - simple dmenu clone
#
.POSIX:

include config.mk

SRC = t4.c desktop.c
OBJ = $(SRC:.c=.o)

all: options t4 tags

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

tags: $(SRC)
	@echo tags file
	@ctags_width_dep.sh $< $(T4_CFLAGS)

clean:
	@echo cleaning
	@rm -f $(NAME) $(OBJ)

install: all
	@echo installing executable file to $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp -f $(NAME) $(DESTDIR)$(PREFIX)/bin
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/$(NAME)

uninstall:
	@echo removing executable file from $(DESTDIR)$(PREFIX)/bin
	@rm -f $(DESTDIR)$(PREFIX)/bin/$(NAME)

.PHONY: all options clean dist install uninstall
