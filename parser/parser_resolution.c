#include "cub3d.h"

static int	find_screen_side(t_all *vars, char *line)
{
	int j;
	int side;

	j = 0;
	while (line[j])
	{
		if (!(line[j] >= '0' && line[j] <= '9'))
			ft_exit("Error: map is invalid");
		j++;
	}
	side = atoi(line);
	if (side < 1)
		ft_exit("Error: map is invalid");
	return (side);
}

static void	free_arr(char **arr, int n)
{
	int i;

	i = 0;
	while (i < n)
		free(arr[i++]);
	free(arr);
}

static void	parser(t_all *vars, int i)
{
	char	**arr;

	if (!(arr = ft_split(vars->map.arr[i], ' ')))
		exit(0); //на ошибку маллока
	if (arr[0][0] == 'R')
	{
		if (!(arr[1]))
			ft_exit("Error: map is invalid");
		if (!(arr[2]))
			ft_exit("Error: map is invalid");
		vars->set.screen_width = find_screen_side(vars, arr[1]);
		vars->set.screen_height = find_screen_side(vars, arr[2]);
		if (arr[3])
			ft_exit("Error: map is invalid");
		free_arr(arr, 3);
	}
	else
		exit(0);
}

int			parser_resolution(t_all *vars, int i, int j)
{
	if (vars->map.arr[i][j] == 'R')
	{
		if (vars->map.arr[i][j + 1] == ' ')
		{
			parser(vars, i);
		/*	if (vars->set.screen_width > vars->set.monitor.x)
				vars->set.screen_width = vars->set.monitor.x;
			if (vars->set.screen_height > vars->set.monitor.y)
				vars->set.screen_height = vars->set.monitor.y;*/
			vars->set.exist_resol++;
			vars->pars.num_of_params++;
			return (1);
		}
		else
			ft_exit("Error: map is invalid");
	}
	return (0);
}
