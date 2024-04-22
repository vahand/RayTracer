##
## EPITECH PROJECT, 2024
## OOP
## File description:
## Makefile
##

CXX = g++

TARGET = raytracer

SRC = 	src/main.cpp	\

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -fPIC

all:
	make core
	make shapes

core: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

graphicals:
	cd shapes && make

clean:
	rm -f $(OBJ)
	cd shapes && make clean

fclean: clean
	rm -f $(TARGET)
	cd shapes && make fclean

re:	fclean all

.PHONY: clean fclean re
