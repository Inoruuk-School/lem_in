/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 04:57:21 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 04:57:21 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : free_all
**-----------------------
** free every param witch the associated function
** @param room
** @param tab
** @param head
*/

void		free_all(t_room **room, char **tab, t_link *head)
{
	free_tab((void **)tab);
	free_link(head);
	free(head);
	free_room(&room);
}

/*
** Function : free_room
**------------------------
** free char *name and each room
** @param room
*/

void		free_room(t_room ***room)
{
	t_room		**h1;

	h1 = *room;
	if (h1)
	{
		while (*h1)
		{
			if ((*h1)->name)
				ft_strdel(&(*h1)->name);
			ft_memdel((void **)&(*h1));
			h1++;
		}
		ft_memdel((void **)&(*h1));
		free(*room);
		*room = NULL;
	}
}

/*
** Function : free_link
** ----------------------
** in each node, free each kids and kid
** @param root
*/

void		free_link(t_link *root)
{
	int		i;

	i = -1;
	if (root)
	{
		while (++i < root->nb_kids && root->kids)
			if (root->kids[i])
				free_link(root->kids[i]);
		if (root->kids && !(i = 0))
		{
			while (i < root->nb_kids)
			{
				free(root->kids[i]);
				root->kids[i++] = NULL;
			}
			free(root->kids);
			root->kids = NULL;
		}
	}
}

/*
** Function : aff_tab
**--------------------
** print each lines in param tab
** @param tab
*/

void		aff_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		if (*tab[i])
			ft_printf(GRN"%s\n"RESET, tab[i]);
	ft_printf("\n");
}

/*
** Function : count_nullkids
**-----------------------------
** 0 = pas bon
** @param root
** @param nb : number of total rooms
** @return number of kids who arent cleaned and therefor at NULL
*/

int			count_nullkids(t_link *root, int nb)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!root || !root->kids)
		return (0);
	while (i < nb)
	{
		if (root->kids[i])
			ret++;
		i++;
	}
	return (ret);
}
