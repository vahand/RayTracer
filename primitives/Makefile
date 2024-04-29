##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

all:
	make -C sphere
	make -C cone
	make -C cylinder
	make -C plane

clean:
	make clean -C sphere
	make clean -C cone
	make clean -C cylinder
	make clean -C plane

fclean: clean
	make fclean -C sphere
	make fclean -C cone
	make fclean -C cylinder
	make fclean -C plane

re:	fclean all

.PHONY: clean fclean re