#include "cub3d.h"

static	void check_data(char *line1, char *line2, char ltr)
{
	if (!(line1))
		exit(0);
	if (ltr == 'C')
		if (line1[0] != 'S' || line1[1])
			exit(0);
	if (ltr == 'S')
		if (line1[0] != ltr || line1[2])
			exit(0);
	if (open(line2, O_RDONLY) == -1)
		exit(0);
}

void	find_path(t_all *vars, int i, t_side *side, char ltr)
{
	char	**arr;

	if (!(arr = ft_split(vars->map.arr[i], ' ')))
		exit(0);
	check_data(arr[0], arr[1], ltr);
	if (arr[2])
		exit(0);

	side->img.img = mlx_xpm_file_to_image(vars->mlx, arr[1], &side->width, &side->height);
	side->img.addr = mlx_get_data_addr(side->img.img, &side->img.bits_per_pixel, &side->img.line_length, &side->img.endian);
	free(arr[1]);
	free(arr[0]);
	free(arr);
}
