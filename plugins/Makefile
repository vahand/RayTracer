##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

all:
	make -C primitives
	make -C materials
	# make -C lights

clean:
	make clean -C primitives
	make clean -C materials
	# make clean -C lights

fclean: clean
	make fclean -C primitives
	make fclean -C materials
	# make fclean -C lights

re:	fclean all

.PHONY: clean fclean re
