/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/01 16:55:06 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/01 16:55:06 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_all(t_room ***room, char ***tab)
{
	int i;

	i = 0;
	if (room && room[0])
	{
		while (room[0][i])
		{
			if ((room[0][i])->name)
				ft_strdel(&(room[0][i]->name));
			free(room[0][i]);
			room[0][i++] = NULL;
		}
		free(room[0]);
	}
	i = 0;
	if (tab && tab[0])
	{
		while (tab[0][i])
			free(tab[0][i++]);
		free(tab[0]);
	}
}

void	aff_tab(char **tab)
{
	int i = 0;

	while (tab[i])
		dprintf(1,GRN"%s\n"RESET,tab[i++]);
}

int		main(void)
{
	t_room	**room;
	t_link	*tube;
	int 	ants;
	char 	**tab;

	ants = 0;
	tab = create_tab();
	aff_tab(tab);
	room = fill_room(tab, &ants, 0, 1);
	dprintf(1, RED"Fill room done\n"RESET);
	aff_room(room);
	if (!(tube = fill_tubes(tab, room)))
		ft_printf("ERROR\n");

	free_all(&room, &tab);
	dprintf(1, RED"Finished\n"RESET);
	return (0);
}