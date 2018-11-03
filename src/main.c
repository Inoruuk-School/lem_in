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

/*
** Function : exception
**-----------------------
** Used only when start and end are linked
** @param end
** @param ants
*/

void	exception(char *end, int *ants)
{
	int i;
	int nb;

	i = 1;
	nb = *ants;
	while (nb > 0)
	{
		ft_printf("L%d-%s ", i++, end);
		nb--;
	}
	write(0, "\n", 1);
	*ants = nb;
}



int		main(void)
{
	t_trie	*root;
	t_tube	*head;
	int		ants;
	char	**tab;

	tab = create_tab();
	if (check_first_step(tab, &ants) <= 0 || ants <= 0)
		error(ants > 0 ? "ERROR : bad room" : "ERROR : ants", tab, NULL, NULL);
	root = fill_room(tab);
	head = parse_tubes(tab, root);
	if (!is_solve2(head))
		error("ERROR : can't solve", tab, &root, &head);
	solver(head, &ants);
	free_all(tab, &head, &root);
	return (EXIT_SUCCESS);
}
