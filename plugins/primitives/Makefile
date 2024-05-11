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
	make -C cube
	make -C wall

clean:
	make clean -C sphere
	make clean -C plane
	make clean -C cylinder
	make clean -C cone
	make clean -C cube
	make clean -C wall

fclean: clean
	make fclean -C sphere
	make fclean -C plane
	make fclean -C cylinder
	make fclean -C cone
	make fclean -C cube
	make fclean -C wall

re:	fclean all

.PHONY: clean fclean re