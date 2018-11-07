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
** Function : aff_tab
**--------------------
** print each line in tab
** @param tab
*/

void	aff_tab(char **tab)
{
	while (*tab)
	{
		ft_printf(RED"%s\n"RESET, *tab);
		tab++;
	}
	ft_printf("\n");
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
	head = parse_tubes(find_links(tab), root, find_end(tab), tab);
	if (head)
		clean_tube(&head);
	if (!is_solve2(head))
		error("ERROR : can't solve", tab, &root, &head);
	aff_tab(tab);
	solver(head, &ants);
	free_all(tab, &head, &root);
	return (EXIT_SUCCESS);
}
