/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/26 02:52:28 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/26 02:52:28 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function check_which2
**---------------------
** @param str given string to check
** @return -1 = end, 0 = room, 1 = start, 2 = comment, 3 = ants, 4 tube
*/

int			check_which2(char *str)
{
	if (str[0] == '#' && !ft_strcmp(str, "##start"))
		return (1);
	else if (str[0] == '#' && !ft_strcmp(str, "##end"))
		return (-1);
	else if (str[0] == '#')
		return 2;
	else if (match(str, "* * *") && check_room(str))
		return (0);
	else if (match(str, "*-*"))
		return (4);
	else if (check_ifdigit(str))
		return (3);
	return (-1);
}

/*
** Function : find_place
**--------------------------
** Find in tree head, the right node to create a new leaf depending on the
** string and name of the current node room's name
** @param head : the tree
** @param str : the string to compare
** @param room : the room's name to compare
*/

void	find_place(t_r_tree *head, t_room *room)
{
	int				i;
	static bool		check = true;

	i = ft_strcmp(room->name, head->room->name);
	if (i == 0)
		error("ERROR : duplicate rooms", NULL, NULL, NULL);
	if (i < 0 && !head->minus && !(check = false))
		head->minus = create_link(room);
	else if (check && i > 0 && !head->plus && !(check = false))
		head->plus = create_link(room);
	if (check && i < 0 && head->minus)
		find_place(head->minus, room);
	else if (check && i > 0 && head->plus)
		find_place(head->plus, room);
	check = true;
}

/*
** Function : fill_rooms
**-----------------------
** Create a list of rooms found in param tab
** @param tab
** @return
*/

void	fill_list(char **tab, t_r_tree *head)
{
	int 		i;

	while (*tab)
	{
		i = check_which2(*tab);
		if ((i == -1 || i == 1) && (tab = next_tab(tab)))
			find_place(head, init_room2(*tab, i));
		else if (!i)
			find_place(head, init_room2(*tab, i));
		else if (i == 4)
			break ;
		tab++;
	}
}

/*
** Function : create_room_list
**------------------------------
** Create a link for a list of rooms
** @param room
** @return
*/

t_r_tree		*create_link(t_room *room)
{
	t_r_tree	*buff;

	if (!(buff = ft_memalloc(sizeof(t_r_tree))))
		return (NULL);
	buff->room = room;
	buff->plus = NULL;
	buff->minus = NULL;
	return (buff);
}

/*
** Function : create_tree
**---------------------------
** create a tree with every rooms in tab
** @param tab
** @return the fresh tree
*/

t_r_tree	*create_tree(char **tab)
{
	t_r_tree	*list;
	int 		i;

	++tab;
	i = check_which(*tab);
	if (i == 2 || i == 3)
	{
		tab = next_tab(tab);
		i = i == 2 ? 1 : -1;
	}
	list = create_link(init_room2(*tab++, i));
	fill_list(tab, list);
	return (list);
}


