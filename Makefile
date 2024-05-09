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
		src/FileManager.cpp	\
		src/save.cpp	\

OBJ = $(SRC:.cpp=.o)

SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS = -fPIC

all: core plugin

core: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ -lconfig -lconfig++ $(SFMLFLAGS)

plugin:
	make -C plugins

clean:
	rm -f $(OBJ)
	make fclean -C plugins

fclean: clean
	rm -f $(TARGET)
	make fclean -C plugins

re:	fclean all

.PHONY: clean fclean re
