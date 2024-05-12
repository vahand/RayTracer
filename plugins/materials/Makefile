##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

all:
	make -C lambertian
	make -C metal
	make -C lightDiffuse
	make -C chessBoard

clean:
	make clean -C lambertian
	make clean -C metal
	make clean -C lightDiffuse
	make clean -C chessBoard

fclean: clean
	make fclean -C lambertian
	make fclean -C metal
	make fclean -C lightDiffuse
	make fclean -C chessBoard

re:	fclean all

.PHONY: clean fclean re