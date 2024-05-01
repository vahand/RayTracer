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

clean:
	make clean -C lambertian
	make clean -C metal
	make clean -C lightDiffuse

fclean: clean
	make fclean -C lambertian
	make fclean -C metal
	make fclean -C lightDiffuse

re:	fclean all

.PHONY: clean fclean re