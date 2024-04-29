##
## EPITECH PROJECT, 2024
## OOP
## File description:
## Makefile
##

SRC	=	src/Plane.cpp	\

NAME	=	raytracer_plane

OBJ	=	$(SRC:.cpp=.o)

all:	$(NAME)

CXXFLAGS = -fPIC

$(NAME):	$(OBJ)
	g++ -shared -o $(NAME).so $(OBJ)
	mv $(NAME).so ../../lib

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME).so
		rm -f ../../lib/$(NAME).so

re:	fclean all
