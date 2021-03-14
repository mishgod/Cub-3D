/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:02:17 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/13 15:02:19 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "gnl/get_next_line.h"
# include "mlx/mlx.h"
# include "lib/libft.h"

typedef struct	s_list
{
	char			*line;
	struct s_list	*next;

}				t_list;

typedef struct	s_vect
{
	double	x;
	double	y;
}				t_vect;

typedef struct	s_vect_int
{
	int	x;
	int	y;
}				t_ivect;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_side_of_the_world
{
	t_img	img;
	int		width;
	int		height;
	int		exist;
}				t_side;

typedef struct	s_texture
{
	t_side	north;
	t_side	south;
	t_side	west;
	t_side	east;
	t_side	sprite;
	int		x;
	double	pos;
}				t_tex;

typedef struct	s_settings
{
	int		argc;
	t_ivect	monitor;
	int		screen_height;
	int		screen_width;
	int		exist_resol;
	double	move_speed;
	double	rot_speed;
}				t_set;

typedef struct	s_plr
{
	double	cam;
	t_vect	pos;
	t_vect	dir;
	t_vect	plane;
}				t_plr;

typedef struct	s_ray
{
	t_vect	delta_dist;
	t_vect	side_dist;
	t_vect	dir;
	t_vect	step;
	double	wall_dist;
	double	wall_x;
	int		side;

}				t_ray;

typedef struct	s_screen
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	step;
}				t_scr;

typedef struct	s_map
{
	int		height;
	char	**arr;
	t_list	*pointer;
	int		x;
	int		y;
}				t_map;

typedef struct	s_spr
{
	t_vect			pos;
	int				order;
	double			dist;
	struct s_spr	*next;

}				t_spr;

typedef struct	s_draw_sprites
{
	t_vect	sprites;
	double	inv_det;
	t_vect	transform;
	int		screen_x;
	int		height;
	int		width;
	t_ivect	draw_start;
	t_ivect	draw_end;
}				t_dspr;

typedef struct	s_color
{
	int r;
	int g;
	int b;
	int clr;
	int exist;
}				t_clr;

typedef struct	s_pars
{
	t_clr	flr;
	t_clr	ceil;
	int		num_of_params;
	int		last_param;
	int		num_of_nswe;
}				t_pars;

typedef struct	s_all
{
	t_tex	tex;
	t_set	set;
	t_img	img;
	t_map	map;
	t_plr	plr;
	t_ray	ray;
	t_scr	scr;
	t_spr	*spr;
	t_pars	pars;

	void	*mlx;
	void	*win;
	int		number_of_sprites;
	double	coef_square;
}				t_all;

typedef struct	s_iheader
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short	planes;
	unsigned short	bit_count;
	unsigned int	compression;
	unsigned int	size_image;
	int				x_pels_per_meter;
	int				y_pels_per_meter;
	unsigned int	clr_used;
	unsigned int	clr_important;
}				t_iheader;

typedef struct	s_fheader
{
	unsigned int	size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	offbits;
}				t_fheader;

typedef struct	s_col
{
	unsigned int color;
}				t_col1;

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
double			absolute(double num);
int				press_key(int keycode, t_all *vars);
int				closed(t_all *vars);
void			ft_background(t_all *vars);
void			my_mlx_pixel_put(t_all *vars, int x, int y, int color);
int				my_mlx_pixel_open(t_img data, int x, int y);
void			player_starting_position(t_all *vars, char **arr);
void			render_map(t_all *vars);
void			walls(t_all *vars, int i, double buf[vars->set.screen_width]);
void			walls_calculations(t_all *vars);
void			ft_spr_add_back(t_all *vars, t_spr **spr, t_spr *new, int i);
t_spr			*ft_spr_new(double x, double y);
t_spr			*ft_spr_num(t_spr *spr, int n);
t_spr			*ft_spr_last(t_spr *spr);
void			ft_spr_add_new_back(t_spr **spr, t_spr *new, int i);
void			ft_free_spr(t_spr *spr);
void			ft_free_list(t_list *list);
void			draw_sprites(t_all *vars, double *z_buffer);
int				parser_floor_ceilling(t_all *vars, int i, int j);
int				parser_resolution(t_all *vars, int i, int j);
void			find_path(t_all *vars, int i, t_side *side, char ltr);
int				parcer_north_south_tex(t_all *vars, int i, int j);
int				parcer_west_east_tex(t_all *vars, int i, int j);
int				parcer_sprite_tex(t_all *vars, int i, int j);
void			ft_valid_map(char **arr, int n, int height);
void			check_elem_maze(char **arr, int i, int j);
void			ft_exit(char *line);
void			ft_screenshot(t_all *vars, int w, int h);
void			ft_parser(t_all *vars);
t_spr			*ft_find_sprites(t_all *vars);
void			sprites_sort(t_all *vars, int n);
void			make_proection(t_all *vars, double *z_buffer);
void			set_vars(t_all *vars, int argc);
char			**map_array(t_list **map, int size);
void			check_input_data(int argc, char **argv);
void			find_coordinations(t_all *vars);

#endif
