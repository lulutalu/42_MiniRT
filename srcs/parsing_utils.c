/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:31:09 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/27 16:46:08 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

char	*trim_free(char *s, char *set)
{
	char	*tmp;

	tmp = ft_strtrim(s, set);
	free(s);
	return (tmp);
}

int	check_size_tab(char **str, int nb)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i != nb)
		return (1);
	return (0);
}

void	count_obj(char *f_path, t_main *m)
{
	int		fd;
	char	*line;

	fd = open(f_path, O_RDONLY);
	if (fd == -1)
		perror_exit("Problem opening file");
	line = get_next_line(fd);
	if (!line)
		exit_error("File empty\n");
	while (line)
	{
		if (line && ft_strcmp_case(line, "\n"))
			m->scn.n_obj++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

float	ft_atof(char *s)
{
	int		sign;
	float	res;
	float	dec;
	int		i;
	int		j;

	i = 0;
	sign = 1;
	res = 0;
	dec = 0;
	if (s[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (s[i] && s[i] != '.')
		res = (res * 10) + (s[i++] - '0');
	if (s[i++] == '.')
	{
		j = ft_strlen(s) - i;
		while (s[i])
			dec = (dec * 10) + (s[i++] - '0');
		res = res + (dec / pow(10, j));
	}
	return (res * sign);
}
