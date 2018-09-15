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

void	free_all(t_room *room, char **tab)
{
	int i;

	i = 0;
	while (R_NAME(i))
		free((R_NAME(i++)));
	i = 0;
	while (tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
	if (room)
		free(room);
}

int		main(void)
{
	t_room	*room;
//	t_link	*tube;
	int 	ants;
	char 	**tab;
	int i=0; //supprimer

//	tube = (t_link *)malloc(sizeof(t_link));
	ants = 0;
	tab = create_tab();
	while (tab[i])
		dprintf(1,GRN"%s\n"RESET,tab[i++]);
	room = fill_room(tab, &ants, 0, 1);
	dprintf(1, RED"Fill room done\n"RESET);
	aff_room(room);
	free_all(room, tab);
	dprintf(1, RED"Finished\n"RESET);
	return (0);
}