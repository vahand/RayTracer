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
	make plugins

core: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ -lconfig -lconfig++

primitive:
	make -C plugins

clean:
	rm -f $(OBJ)
	make fclean -C plugins

fclean: clean
	rm -f $(TARGET)
	make fclean -C plugins

re:	fclean all

.PHONY: clean fclean re
