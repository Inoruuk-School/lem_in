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

void	exeption(t_link *end, int *ants)
{
	int i;
	int nb;

	i = 1;
	nb = *ants;
	while (nb > 0)
	{
		ft_printf("L%d-%s ", i++, end->room->name);
		nb--;
	}
	write(0, "\n", 1);
	*ants = nb;
}

/*
** Function : error
**------------------
** print str and free the rest of the params
** @param str : error to print
** @param tab : being freed
** @param room : being freed
** @param root : being freed
*/

void	error(char *str, char **tab, t_room **room, t_link *root)
{
	ft_printf(RED"%s\n"RESET, str);
	if (tab)
		free_tab((void **)tab);
	if (room)
		free_room(&room);
	if (root)
		free_link(root);
	exit(0);
}

int		main(void)
{
	t_room	**room;
	t_link	*tube;
	int		ants;
	char	**tab;
	int		nb_room;

	room = NULL;
	tube = NULL;
	tab = create_tab();
	if ((nb_room = check_first_step(tab, &ants, 0)) <= 0 || ants <= 0)
		error(ants > 0 ? "ERROR : bad room" : "ERROR : ants", tab, room, tube);
	room = fill_room(tab, nb_room);
	if (!room || !check_duplicate_rooms(room, nb_room))
		error("ERROR : Duplicate rooms", tab, room, tube);
	tube = fill_tubes(tab, room, nb_room);
	clean_tree(&tube);
	if (!is_solve(tube))
		error("ERROR : can't solve", tab, room, tube);
	aff_tab(tab);
	solver(tube, &ants);
	free_all(room, tab, tube);
	return (EXIT_SUCCESS);
}
