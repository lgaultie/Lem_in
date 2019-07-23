/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:47:08 by lgaultie          #+#    #+#             */
/*   Updated: 2019/07/23 16:55:51 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** check_start_end() reviews all rooms to check if there is a start and an end.
*/

static int	check_start_end(int error, t_farm *farm)
{
	int		check_startend;
	t_rooms	*tmp_rooms;

	check_startend = 0;
	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		if (tmp_rooms->start_end == 1 || tmp_rooms->start_end == 2)
			check_startend++;
		tmp_rooms = tmp_rooms->next;
	}
	if (check_startend != 2)
		error = -1;
	return (error);
}

/*
** is_start_end() tells which line is start (1), and end (2).
*/

int			is_start_end(int start_end, char *line)
{
	if (line && ft_strcmp(line, "##start") == 0)
		start_end = 1;
	else if (line && ft_strcmp(line, "##end") == 0)
		start_end = 2;
	return (start_end);
}

/*
** check_line() prints the line, and checks if we have an empty line. If that
** is the case, it returns ERROR.
*/

int			check_line(char *line, int error)
{
	if (line && ft_strcmp(line, "") == 0)
		error = -1;
	ft_putendl(line);
	return (error);
}

/*
** free_when_needed() frees line.
*/

void		free_when_needed(char *line)
{
	if (line)
		free(line);
}

/*
** read_input() reads every line of the map file, except comments, then calls
** different checking functions to check if the map is valid.
*/

int			read_input(t_farm *farm, int line_nb, int error, int start_end)
{
	char		*line;
	int			ret;

	line = NULL;
	ret = 1;
	while (ret != 0)
	{
		free_when_needed(line);
		ret = get_next_line(0, &line);
		error = check_line(line, error);
		start_end = is_start_end(start_end, line);
		error = check_nb_ants(line_nb, farm, line, error);
		if (line && error == 0 && line_nb > 1 && line[0] != '#')
		{
			if (parse(farm, line, start_end) == ERROR)
				error = -1;
			start_end = 0;
		}
		if (line && line[0] == '#' && line[1] != '#')
			line_nb--;
		line_nb++;
	}
	error = check_start_end(error, farm);
	return (error);
}
