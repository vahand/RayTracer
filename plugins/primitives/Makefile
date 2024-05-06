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
	make -C cone

clean:
	make clean -C sphere
	make clean -C plane
	make clean -C cylinder
	make clean -C cone

fclean: clean
	make fclean -C sphere
	make fclean -C plane
	make fclean -C cylinder
	make fclean -C cone

re:	fclean all

.PHONY: clean fclean re