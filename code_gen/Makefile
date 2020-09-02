# Do not print when we change of directory
MAKEFLAGS += --no-print-directory

CC		:= g++
C_FLAGS := -std=c++11 -Wall -Wextra -Werror -g
INCLUDE_PATH = src/header
INCLUDE_PATH_TEST = tests/header
LIBRARIES	:= -pthread
TARGET =
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES  :=	$(wildcard $(SRCDIR)/*.cpp)
INCLUDES :=	$(wildcard $(INCLUDE_PATH)/*.hpp)
OBJECTS  :=	$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


# $(BINDIR)/$(TARGET): $(OBJECTS)
# 	mkdir -p $(BINDIR)
# 	$(CC) -o $@ $^ $(CFLAGS) $(LIBRARIES)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@ echo "objects"
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE_PATH)

clean:
	$(RM) $(OBJDIR)/* $(BINDIR)/*

test-code-write:
	@ cd tests $(MAKE) && make run TARGET=test_lib_code_w || true

test-code-comprehension:
	@ cd tests $(MAKE) && make run TARGET=test_code_comprehension || true

test-compact:
	@ cd tests $(MAKE) && make run TARGET=test_compact || true

test:
	@ cd tests $(MAKE) && make run

.PHONY: clean
