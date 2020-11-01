CC = opt_0
CFLAGS ?= -lcurses -Wall -Wextra -Werror -g

CEXTENSION = opt_1
HEXTENSION = opt_2

INCLUDE_PATH = opt_3

TARGET = opt_4

SRCDIR = opt_5
OBJDIR = opt_6
BINDIR = opt_7

SOURCES  := $(wildcard $(SRCDIR)/*.$(CEXTENSION))
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.$(HEXTENSION))
OBJECTS  := $(SOURCES:$(SRCDIR)/%.$(CEXTENSION)=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "[\033[1;32mSuccess\033[0m] All objects were built."

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.$(CEXTENSION)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

nowerror:
	@make CFLAGS="-lcurses -g" --no-print-directory

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
