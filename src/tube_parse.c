/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tube_parse.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 06:09:29 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 06:09:29 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : check_second_step
**------------------------------
** check tab to see if there are only comments, command(for now?) and links
** @param tab to check
** @return true if good false if not
*/

void		check_second_step(char **tab, t_room **room)
{
	bool	check;

	check = true;
	while (check && *tab)
	{
		while (*tab && **tab == '#')
			tab++;
		if (*tab && **tab == 'L')
		{
			**tab = '\0';
			check = false;
		}
		else if (*tab && (!match(*tab, "*-*") || !check_name2(*tab, room)))
		{
			**tab = '\0';
			check = false;
		}
		tab++;
	}
	if (!check)
		while (*tab)
		{
			**tab = '\0';
			tab++;
		}
}

/*
** Function : search_links
**--------------------------
** Search every link with the room "name" in tab
** @param tab
** @param name
** @param nb_rooms
** @return
*/

char		**search_links(char **tab, char *name, int nb_rooms)
{
	char	**split;
	char	*buff;
	void	*start;

	if (!(split = ft_memalloc(sizeof(char *) * (nb_rooms))))
		return (NULL);
	start = split;
	while (*tab)
	{
		if (**tab != '#' && (buff = ft_strstr(*tab, name)))
		{
			if (buff == *tab && (buff = 1 + ft_strstr(buff, "-")))
			{
				if (!(*split++ = ft_strdup(buff)))
					return (NULL);
			}
			else if (!(*split++ = ft_strndup(*tab, buff - *tab - 1)))
				return (NULL);
			**tab = '\0';
		}
		tab++;
	}
	return (check_duplicate(start));
}

/*
** Function : tube_search
**------------------------
** Search each nodes to find name
** @param name : focus of the search
** @param tube : struct in wich we search each nodes
** @return : the node where name has been found or NULL
*/

t_link		*tube_search(t_link *tube, char *name)
{
	int		i;
	t_link	*buff;

	i = 0;
	if (!tube)
		exit(0);
	if (!ft_strcmp(tube->room->name, name))
		return (tube);
	if (tube->kids)
	{
		while (tube->kids[i])
		{
			buff = tube_search(tube->kids[i], name);
			if (!buff || ft_strcmp(name, buff->room->name) != 0)
				i++;
			else
				return (buff);
		}
	}
	return (NULL);
}

/*
** Function : create_tubes
** ------------------------
** @param tab
** @param root
** @param room
** @param nb : numder of rooms
** @return
*/

t_link		*create_tubes(char **tab, t_link *root, t_room **room, int nb)
{
	char	**split;

	split = search_links(tab, root->room->name, nb);
	root->kids = create_kids(split, count_split(split), room);
	free_tab((void **)split);
	path(root, tab, room, nb);
	return (root);
}

/*
** Function fill_tube
** -------------------
** @param tab
** @param room
** @return
*/

t_link		*fill_tubes(char **tab, t_room **room, int nb_room)
{
	t_link		*root;
	char		**cpy;

	tab++;
	while (!ft_strstr(*tab, R_NAME(0)))
		tab++;
	check_second_step(++tab, room);
	cpy = copy_tab(tab);
	if (!(root = create_root(search_end(room))))
		return (NULL);
	root = create_tubes(cpy, root, room, nb_room);
	free_tab((void **)cpy);
	return (root);
}
