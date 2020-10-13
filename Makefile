# - inc/
#     - *.h
# - src/
#     - *.c
#     - *.cpp
# - bin/
#     - *.o
# - main

TARGET := bin/main
SOURCES := $(wildcard src/*.c src/*.cpp)
OBJECTS := $(patsubst src%,bin%, $(patsubst %.c,%.o, $(patsubst %.cpp,%.o,$(SOURCES))))

INCLUDE := -I.
LIBPATH :=
LIBS := -lncurses

FLAGS := -Wall -Wextra -ggdb
CCFLAGS := $(FLAGS) -std=c11
CXXFLAGS := $(FLAGS)  -Werror -std=c++17

CC := gcc
CXX := g++

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $(TARGET) $(LIBPATH) $(LIBS)

%.o: ../src/%.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf bin/*
	rm -f $(TARGET)