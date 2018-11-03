/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_tube_tool.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/31 04:44:20 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 04:44:20 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : make_tube
**----------------------
** Malloc a tube
** @param room
** @return
*/

t_tube		*make_tube(t_room *room)
{
	t_tube		*tube;

	tube = (t_tube *)ft_memalloc(sizeof(t_tube));
	if (!tube)
		return (NULL);
	tube->room = room;
	tube->child = NULL;
	tube->bro = NULL;
	tube->nb = tube->room->status == 1 ? 1 : 0;
	return (tube);
}

/*
** Function : make_bro
** @param current
** @param room
*/

void		make_bro(t_tube *current, t_room *room)
{
	t_tube		*bro;

	bro =current;
	while (bro->bro != NULL)
		bro = bro->bro;
	bro->bro = make_tube(room);
}

/*
** Function : check_second_step
**------------------------------
** check tab to see if there are only comments, command(for now?) and links
** @param tab to check
** @return true if good false if not
*/

void		check_links(char **tab, t_trie *root)
{
	bool	check;

	check = true;
	while (check && *tab)
	{
		while (*tab && **tab == '#')
			tab++;
		if (!*tab)
			break ;
		if (*tab && **tab == 'L' && !(check = false))
			**tab = '\0';
		else if (*tab && (!match(*tab, "*-*") || !check_name3(*tab, root)))
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
** Function : check_name3
**--------------------------
** @param str : link : "*-*"
** @param root : trie
** @return : true if the rooms in the given link are found, false if not
*/

bool		check_name3(char *str, t_trie *root)
{
	char	*str2;

	str2 = 1 + ft_strchr(str, '-');
	str[str2 - str - 1] = '\0';
	if (!getroom(root, str) || !getroom(root, str2))
		return (false);
	str[str2 - str - 1] = '-';
	return (true );
}

void		duplicate_link2(char **split) // delete duplicate but doesnt delte 1-2 2-1 yet
{
	int i;
	int j;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		while (split[i] && !split[i][0])
			i++;
		j = i + 1;
		while (split[i] && split[j])
		{
			if (!ft_strcmp(split[i], split[j]))
				split[j][0] = '\0';
			j++;
		}
		i++;
	}
}

void		duplicate_link(char **split) // delete duplicate but doesnt delte 1-2 2-1 yet
{
	char 	**buff;
	if (!split)
		return ;
	while (*split)
	{
		buff = split + 1;
		while (**split && *buff)
		{
			if (!ft_strcmp(*split, *buff))
				**buff = '\0';
			buff++;
		}
		split++;
	}
}