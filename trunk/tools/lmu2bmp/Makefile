SHELL = /bin/sh
TARGET = lmu2bmp
CC = g++
SRCS =  *.cpp
CFLAGS = -Os -s -Wall -Wextra -ansi -pedantic $(shell sdl-config --cflags)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti

LIBS = -lSDL_image $(shell sdl-config --libs)

all:
	$(CC) -o $(TARGET) $(SRCS) $(CXXFLAGS) $(LIBS)
clean:
	rm -f $(TARGET)
