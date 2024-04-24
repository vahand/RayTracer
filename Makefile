##
## EPITECH PROJECT, 2024
## OOP
## File description:
## Makefile
##

CXX = g++

TARGET = raytracer

SRC = 	src/main.cpp	\
		src/Core.cpp	\
		src/Loader.cpp	\
		src/Parser.cpp	\

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -fPIC

all:
	make core
	make shape

core: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ -lconfig -lconfig++

shape:
	cd shapes && make

clean:
	rm -f $(OBJ)
	cd shapes && make clean

fclean: clean
	rm -f $(TARGET)
	cd shapes && make fclean

re:	fclean all

.PHONY: clean fclean re
