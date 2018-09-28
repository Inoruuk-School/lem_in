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
//	t_link	*tube;
	int 	ants;
	char 	**tab;
	int 	nb_room;

	ants = 0;
	room = NULL;
	tab = create_tab();
	aff_tab(tab);
	nb_room = check_first_step(tab, &ants);
	dprintf(1, RED"First check done : nb_room : %-10d ants = %d\n"RESET, nb_room, ants);
	if (nb_room > 0)
		room = fill_room(tab, nb_room);
	dprintf(1, RED"Fill room done\n"RESET);
	if (room && check_rooms(room, nb_room))
		aff_room(room, nb_room);
	else
		ft_printf(RED"Mauvais check_rooms\n"RESET);
//	if (!(tube = fill_tubes(tab, room)))
//		ft_printf(BLU"ERROR\n"RESET);
//	free_all(&room, &tab);
	dprintf(1, RED"Finished\n"RESET);
	return (0);
}