CC = g++
CFLAGS ?= -lcurses -Wall -Wextra -Werror -g

CEXTENSION = cpp
HEXTENSION = h

INCLUDE_PATH = ./include

TARGET = codegen

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = .

BINPATH := $(shell echo $(PATH) | cut -d ":" -f2)

SOURCES  := $(wildcard $(SRCDIR)/*.$(CEXTENSION))
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.$(HEXTENSION))
OBJECTS  := $(SOURCES:$(SRCDIR)/%.$(CEXTENSION)=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "[\033[1;32mSuccess\033[0m] Makefile is done."

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.$(CEXTENSION)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

nowerror:
	@make CFLAGS="-lcurses -g" --no-print-directory

move_to_bin:
	mv $(BINDIR)/$(TARGET) ${BINPATH}

silent_clean:
	@rm -f $(OBJDIR)/*.o
	@rm -f $(OBJDIR)/*.gcda
	@rm -f $(OBJDIR)/*.gcno
	@rm -f $(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
