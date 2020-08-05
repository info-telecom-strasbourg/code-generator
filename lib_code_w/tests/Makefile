TARGET   =	test


CC		:= g++
C_FLAGS := -std=c++11 -Wall -Wextra -Werror -g
INCLUDE_PATH = ../src/header
LIBRARIES	:= -pthread
SRCDIR   =	.
OBJDIR   =	../obj
BINDIR   =	../bin
SOURCES  :=	$(wildcard $(SRCDIR)/$(TARGET).cpp)
INCLUDES :=	$(wildcard $(INCLUDE_PATH)/*.hpp)
OBJECTS  :=	$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBRARIES)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH) -I./header



clean:
	$(RM) $(OBJDIR)/* $(BINDIR)/*

run:
	@ make >/dev/null
	@ ../bin/$(TARGET) || true
.PHONY: clean
