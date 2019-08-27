//faire header 42
#include <lem_in.h>

void		print_tab_paths(t_farm *farm)
{
	int	i;
	t_paths	*tmp_tab;

	i = 0;
	while (i <= farm->nb_paths)
	{
		tmp_tab = farm->all_paths[i];
		ft_putstr("i = ");
		ft_putnbr(i);
		ft_putchar('\n');
		while (tmp_tab)
		{
			int x = 0;
			while(x < tmp_tab->length)
			{
				ft_putnbr(tmp_tab->path[x]);
				ft_putchar(' ');
				x++;
			}
			ft_putchar('\n');
			tmp_tab = tmp_tab->next;
		}
		ft_putstr("\n-----------tableau de save_paths-------------\n");
		i++;
	}
	ft_putchar('\n');
}

void		print_free_rooms(t_farm *farm)
{
	t_rooms *tmp;

	tmp = farm->rooms;
	ft_putstr("--------------\n");
	while (tmp)
	{
		if (tmp->reserved == 1)
		{
			ft_putstr("salle ");
			ft_putnbr(tmp->room_id);
			ft_putstr(" reserved");
			ft_putchar(' ');
		}
		if (tmp->reserved == 0)
		{
			ft_putstr("salle ");
			ft_putnbr(tmp->room_id);
			ft_putstr(" libre");
			ft_putchar(' ');
		}
		ft_putchar('\n');
		tmp = tmp->next;
	}
	ft_putstr("--------------\n");
}
