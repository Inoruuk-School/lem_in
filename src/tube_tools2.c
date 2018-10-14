/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tube_tools2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 04:24:34 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 04:24:34 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : count_split
** @param split
** @return
*/

int			count_split(char **split)
{
	int i;

	i = 0;
	if (split)
	{
		while (*split)
		{
			if (**split)
				i++;
			split++;
		}
	}
	return (i);
}

/*
** Function : create_kids
** @param split
** @param nb
** @param room
** @return
*/

t_link		**create_kids(char **split, int nb, t_room **room)
{
	t_link	**kids;
	t_link	**head;
	int		i;

	head = NULL;
	if (nb > 0)
	{
		i = 0;
		if (!(kids = ft_memalloc(sizeof(t_link *) * (nb + 1))))
			return (NULL);
		head = kids;
		while (i < nb)
		{
			if (!(*kids = ft_memalloc(sizeof(t_link))))
				return (NULL);
			kids++;
			i++;
		}
		init_kids(head, split, room);
	}
	return (head);
}

/*
** Function search_room
** @param room
** @param name
** @return
*/

t_room		*search_room(t_room **room, char *name)
{
	if (!room)
		return (NULL);
	while (*room)
	{
		if (ft_strcmp(name, (*room)->name) == 0)
			return (*room);
		room++;
	}
	return (NULL);
}

/*
** Function : path
** -----------------
** Create every path
** @param root
** @param tab
*/

void		path(t_link *root, char **tab, t_room **room, int nb)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	if (root)
	{
		while (root->kids && root->kids[i])
		{
			path(root->kids[i], tab, room, nb);
			i++;
		}
		if (root->room && root->room->status != 1 && root->room->status != -1)
		{
			split = search_links(tab, root->room->name, nb);
			root->kids = create_kids(split, count_split(split), room);
			free_tab((void **)split);
			while (root->kids && root->kids[j])
				path(root->kids[j++], tab, room, nb);
		}
	}
}
