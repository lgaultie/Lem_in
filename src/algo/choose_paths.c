/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 11:03:23 by lgaultie          #+#    #+#             */
/*   Updated: 2019/08/28 14:34:49 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** unvisit_rooms() checks all the rooms and set their `visited` attribute to 0.
*/

static void	unvisit_rooms(t_farm *farm)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms)
	{
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
}

/*
** check_paths() checks if we have two similar paths in our paths strusture.
** If this is the case, we have found all the paths possible, and we no longer
** need to call our algorithm. We delete the first similar path.
*/

int			check_paths(t_farm *farm)
{
	t_paths	*current_path;
	t_paths	*compared_path;
	int		i;

	ft_putstr("check paths\n");
	current_path = farm->paths;
	while (current_path)
	{
		compared_path = farm->paths;
		while (compared_path)
		{
			if (current_path != compared_path \
				&& current_path->length == compared_path->length)
			{
				i = 0;
				while (i < compared_path->length \
					&& current_path->path[i] == compared_path->path[i])
					i++;
				if (i == compared_path->length)
				{
					ft_putstr("There is 2 similar paths, we delete the first similar path.\n");
					delete_path(farm, current_path);
					return (SUCCESS);
				}
			}
			compared_path = compared_path->next;
		}
		current_path = current_path->next;
	}
	return (FAILURE);
}

/*
** find_paths() calls algo() and checks what it returns.
** If it returns -2, we found the end room, so our BFS is complete. We save the
** path in our structure and reserve the rooms.
** If it returns another number (a room id), it means we are stucked here. We
** call backtrack_paths() to unreserve the room.
*/

int			find_paths(t_farm *farm, int **matrice)
{
	int				ret_algo;
	int				ret_fill_path;
	static int		ret_backtrack = -1;
	static int		just_deleted = -1;

	while ((ret_algo = algo(farm, matrice)) == -2)
	{
		if (init_paths(farm) == ERROR || ((ret_fill_path = fill_path(farm)) == ERROR))
			return (ERROR);
		if (ret_fill_path == FAILURE)
			return (FAILURE);
		free_queue(farm);
		fill_reserved(farm);
		if (ret_backtrack != -1)
		{
			path_to_delete(farm, ret_backtrack);
			ret_backtrack = -1;
			just_deleted = 1;
		}
		if (just_deleted != 1)
		{
			if (save_path(farm, farm->paths) == ERROR)
				return (ERROR);
		}
		just_deleted = -1;
	}
	ft_putstr("ret_algo: ");
	ft_putnbr(ret_algo);
	ft_putchar('\n');
	if (ret_algo != -2)
	{
		unvisit_rooms(farm);
		ret_backtrack = backtrack_paths(ret_algo, farm);
		ft_putstr("ret_backtrack: ");
		ft_putnbr(ret_backtrack);
		ft_putchar('\n');
		if (ret_backtrack == ERROR)
			return (ERROR);
	}
	// print_free_rooms(farm); // TMP
	return (SUCCESS);
}
