/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   room_tool.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 05:25:38 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 05:25:38 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : next_tab
**----------------------
** Search in param tab the next non comment line
** @param tab
** @return
*/

char		**next_tab(char **tab)
{
	while (tab && *tab && **tab == '#')
		tab++;
	return (tab);
}

/*
** Function check_which
**---------------------
** @param str given string to check
** @return -1 = end, 0 = room, 1 = start, 3 = tubes, 4 = comment, 5 = ants
*/

int			check_which(char *str)
{
	if (str[0] == '#' && !ft_strcmp(str, "##end"))
		return (-1);
	else if (str[0] == '#' && !ft_strcmp(str, "##start"))
		return (1);
	else if (str[0] == '#')
		return (4);
	else if (match(str, "* * *") && check_room(str))
		return (0);
	else if (match(str, "*-*"))
		return (3);
	else if (check_ifdigit(str))
		return (5);
	return (-1);
}

/*
** Function : check_room
**-------------------------
** @param str : string to check
** @return true if the string is a room, false if it isn't
** Create a char ** and check if each split is the correct format
** then check if a room with the same name does not exist
** then free the created split
*/

bool		check_room(char *str)
{
	char	**tab;
	bool	check;

	check = true;
	if (!(tab = ft_strsplit(str, ' ')))
		exit(0);
	if (!tab[0] || !tab[1] || !tab[2])
	{
		free_tab((void **)tab);
		return (false);
	}
	if (!check_ifalphanum(tab[0]) || tab[0][0] == 'L' || tab[0][0] == '#')
		check = false;
	if (!check_ifdigit(tab[1]) && !check_ifdigit(tab[2]))
		check = false;
	free_tab((void **)tab);
	return (check);
}

/*
** Function : init_room
**------------------------
** cerate the room and put it in the trie
** @param str : contain name, x & y
** @param status 0 = normal, 1 = start, -1 = end
** @param root : trie which will be filled with rooms
*/

void		init_room(char *str, int status, t_trie *root, char **tab)
{
	char	**strtab;
	t_room	*room;
	int		i;

	i = 0;
	if (!(strtab = ft_strsplit(str, ' ')) ||\
			!(room = ft_memalloc(sizeof(t_room))))
		exit(0);
	if (!strtab[0] || !strtab[1] || !strtab[2])
	{
		free(room);
		error("ERROR : bad room", tab, NULL, NULL);
	}
	room->status = status;
	room->name = ft_strdup(strtab[0]);
	room->coord_x = ft_atoi(strtab[1]);
	room->coord_y = ft_atoi(strtab[2]);
	room->hantz = status == 1 ? true : false;
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
	put_room(root, room, room->name);
}
