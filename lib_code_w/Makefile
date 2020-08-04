CC		:= g++
C_FLAGS := -std=c++11 -g -pthread

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= test.exe
else
EXECUTABLE	:= test
endif

all: 	$(EXECUTABLE)

clean:
	$(RM) $(EXECUTABLE) main.cpp

run: all
	$(EXECUTABLE)

$(EXECUTABLE): *.cpp
	$(CC) $(C_FLAGS) -I -L $^ -o $@ $(LIBRARIES)
