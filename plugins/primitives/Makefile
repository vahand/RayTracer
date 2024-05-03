##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

all:
	make -C sphere
	make -C plane
	make -C cylinder

clean:
	make clean -C sphere
	make clean -C plane
	make clean -C cylinder

fclean: clean
	make fclean -C sphere
	make fclean -C plane
	make fclean -C cylinder

re:	fclean all

.PHONY: clean fclean re