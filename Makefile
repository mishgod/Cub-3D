NAME	= libcub.a

CC		= gcc

CFLAGS	=  -Wall #-fsanitize=address #-Werror -Wextra

SOURCES	= exe.c gnl/get_next_line.c gnl/get_next_line_utils.c lists.c utils.c press_key.c \
                player_starting_position.c walls/draw_walls.c  walls/walls_calculations.c sprites/sprites_structures.c free_all.c \
               sprites/sprites.c parser/parser_floor_ceilling.c parser/parser_resolution.c parser/parser_find_path.c parser/parser_textures.c \
                parser/parser_valid_map.c ft_background.c screenshot.c parser/parser.c parser/parser_valid_map_utils.c

OBJECTS	= $(SOURCES:.c=.o)

HEADER	= cub3d.h -Ignl/get_next_line.h -Imlx/mlx.h -Imy_lib/libft.h

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

	${CC} ${CFLAGS} -L. -lcub -Lmlx -lmlx -Llib -lft -framework OpenGL -framework AppKit -o $(NAME) \
	&& ./$(NAME) map.cub dgf

all: $(NAME)

.c.o:
	${CC} $(CFLAGS) -I ${HEADER} -c $< -o $@

.PHONY: all clean fclean re

clean:
	-rm -f $(OBJECTS)

fclean: clean
	-rm -f $(NAME)

re: fclean all