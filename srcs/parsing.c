/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:57:02 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/27 17:07:50 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	fill_obj_tab(char **info, t_main *m)
{
	static int	i = -1;

	i++;
	if (!ft_strncmp(info[0], "A", 1) && ft_strlen(info[0]) == 1)
		fill_obj_a(info, m, i);
	else if (!ft_strncmp(info[0], "C", 1) && ft_strlen(info[0]) == 1)
		fill_obj_c(info, m, i);
	else if (!ft_strncmp(info[0], "L", 1) && ft_strlen(info[0]) == 1)
		fill_obj_l(info, m, i);
	else if (!ft_strncmp(info[0], "sp", 2) && ft_strlen(info[0]) == 2)
		fill_obj_sp(info, m, i);
	else if (!ft_strncmp(info[0], "pl", 2) && ft_strlen(info[0]) == 2)
		fill_obj_pl(info, m, i);
	else if (!ft_strncmp(info[0], "cy", 2) && ft_strlen(info[0]) == 2)
		fill_obj_cy(info, m, i);
	else
	{
		printf("(%s)\n", info[0]);
		exit_error_free("Invalid input : ID\n", m->scn.obj);
	}
}

void	get_scn(char *f_path, t_main *m)
{
	int		fd;
	char	*line;
	char	**info;

	fd = open(f_path, O_RDONLY);
	if (fd == -1)
		perror_exit("Problem opening file");
	line = get_next_line(fd);
	while (line)
	{
		if (line && ft_strcmp_case(line, "\n"))
		{
			line = trim_free(line, "\n");
			info = ft_split(line, ' ');
			fill_obj_tab(info, m);
			ft_tab_free((void **)info);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	parse(int ac, char **av, t_main *m)
{
	check_args(ac, av);
	init_scn(&m->scn);
	count_obj(av[1], m);
	init_obj(m);
	get_scn(av[1], m);
}
