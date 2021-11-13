# Cub-3D

## Description

This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. 
The goal is to make a dynamic view inside a maze, in which you need to find your way.

Project is used the `miniLibX`.

Here my own library - [libft](https://github.com/mishgod/libft) was used.

Compilation was with flags: `gcc -Wall -Wextra -Werror -L. -lcub -Lmlx -lmlx -Llib -lft -framework OpenGL -framework AppKit`.

Project has written in accordance with the Norminette.

No memory leaks.

## Management

The left and right arrow keys of the keyboard allow you to look left and
right in the maze.

◦ The W, A, S, and D keys allow you to move the point of view through
the maze.

◦ Pressing ESC must close the window and quit the program.

## Usage

Use `make` to compile the executable file.

Use `./Cub-3D map.cub` to launch program. `map.cub` is the map, so you can use some different maps that must be valid.

You can use some different textures. To do this just download it to the direction `textures` in `.xpm` format. It may have different resolution.

Use `/Cub-3D map.cub --save` to make the screenshot `save.bmp`.

Use `make re` to recompile.

Use `make clean` to delete `.o`files.

Use `make fclean` to delete `Cub-3D`, `libft.a` and `.o`files.