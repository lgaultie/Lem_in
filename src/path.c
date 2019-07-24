/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:15:36 by cmouele           #+#    #+#             */
/*   Updated: 2019/07/16 13:17:37 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	retrieve_path(t_farm *farm, t_paths *path, int room_id)
{
	static int	i = 0;
	t_rooms		*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms != NULL)
	{
		if (tmp_rooms->room_id == room_id)
		{
			path->path[i] = tmp_rooms->room_id;
			i++;
			break ;
		}
		tmp_rooms = tmp_rooms->next;
	}
	while (i < path->length)
		retrieve_path(farm, path, tmp_rooms->parent->room_id);
	return (SUCCESS);
}

static int	find_layer(t_farm *farm)
{
	t_rooms	*tmp_rooms;

	tmp_rooms = farm->rooms;
	while (tmp_rooms != NULL)
	{
		if (tmp_rooms->start_end == 2)
			return (tmp_rooms->layer);
		tmp_rooms = tmp_rooms->next;
	}
	return (SUCCESS);
}

int			fill_path(t_farm *farm)
{
	t_paths	*tmp_path;
	t_rooms	*tmp_rooms;
	int		layer;

	tmp_path = farm->paths;
	tmp_rooms = farm->rooms;
	layer = find_layer(farm);
	printf("layer: %d\n", layer);
	while (tmp_path->path != NULL)
		tmp_path = tmp_path->next;
	tmp_path->length = layer + 1;
	tmp_path->path = (int*)malloc(sizeof(int) * (layer + 1));
	while (tmp_rooms != NULL)
	{
		if (tmp_rooms->start_end == 2)
			retrieve_path(farm, tmp_path, tmp_rooms->room_id);
		tmp_rooms = tmp_rooms->next;
	}
	return (SUCCESS);
}

int			init_paths(t_farm *farm)
{
	t_paths	*tmp;
	t_paths	*new;
	int		i;

	i = 0;
	while (i < farm->ants)
	{
		tmp = farm->paths;
		if ((new = ft_memalloc(sizeof(t_paths))) == NULL)
			return (ERROR);
		if (tmp != NULL)
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			farm->paths = new;
		new->id_ant = i;
		new->next = NULL;
		i++;
	}
	return (SUCCESS);
}
