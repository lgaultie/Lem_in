/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:51:58 by lgaultie          #+#    #+#             */
/*   Updated: 2019/09/01 16:37:45 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
#include <stdio.h> // TMP

# define SUCCESS 1
# define FAILURE 0
# define ERROR -1
# define ERROR_MSG "ERROR"

typedef struct			s_queue
{
	int					id;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_paths
{
	int					length;
	int					*path;
	struct s_paths		*prev;
	struct s_paths		*next;
}						t_paths;

typedef struct			s_links
{
	struct s_links      *next;
	char                *name;
}						t_links;

typedef struct			s_rooms
{
	char				*name;
	t_links				*links;
	int					room_id;
	int					x_pos;
	int					y_pos;
	int					start_end;
	int					visited;
	int					reserved;
	int					nb_links;
	int					layer;
	struct s_rooms		*prev;
	struct s_rooms		*next;
	struct s_rooms		*parent;
}						t_rooms;

typedef struct			s_rooms_id
{
	int					room_id;
	struct s_rooms_id	*next;
}						t_rooms_id;

typedef struct			s_farm
{
	int					nb_paths;
	int					ants;
	int					total_rooms;
	t_queue				*queue;
	t_rooms				*rooms;
	t_rooms_id			*blocking_rooms;
	t_paths				*paths;
	// t_paths				*deleted_paths;
	t_paths				**all_paths;
}						t_farm;

int		read_input(t_farm *farm, int line_nb, int error, int start_end);
int		parse(t_farm *farm, char *line, int start_end);
int		parse_rooms(t_farm *farm, char *line, int start_end);
int		parse_links(t_farm *farm, char *line);
int		**matrice_create(t_farm *farm);
int		algo(t_farm *farm, int **matrice);
int		queue(t_farm *farm, int room_id);
int		unqueue(t_farm *farm);
void 	free_matrice(t_farm *farm, int **matrice);
void	free_rooms(t_rooms *rooms);
void	free_queue(t_farm *farm);
void	free_paths(t_farm *farm);
int 	free_farm_error(t_farm *farm);
int		free_tab_error(char **tab);
int		init_paths(t_farm *farm);
int		fill_path(t_farm *farm);
int		save_path(t_farm *farm, t_paths *paths);
int		fill_reserved(t_farm *farm);
int		backtrack_paths(int block, t_farm *farm);
void	delete_path(t_farm *farm, t_paths *path);
int		find_paths(t_farm *farm, int **matrice);
int		check_paths(t_farm *farm);
int		path_to_delete(t_farm *farm, int room_id);
void	free_all_paths(t_farm *farm);
void	free_blocking_room(t_farm *farm);
int		check_starters(t_farm *farm, int **matrice);
//print functions
void	print_tab_paths(t_farm *farm);
void	print_free_rooms(t_farm *farm);
void	print_all_paths(t_farm *farm);

#endif
