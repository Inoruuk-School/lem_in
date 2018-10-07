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
** @return 1 = room, 0 = tubes, 2 = start, 3 = end, 4 = comment, 5 = ants
*/

int			check_which(char *str)
{
	if (str[0] == '#' && ft_strnstr(str, "##start", 7))
		return (2);
	else if (str[0] == '#' && ft_strnstr(str, "##end", 5))
		return (3);
	else if (str[0] == '#')
		return (4);
	else if (match(str, "* * *") && check_room(str))
		return (1);
	else if (match(str, "*-*"))
		return (0);
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
	if (!check_ifalphanum(tab[0]) || tab[0][0] == 'L' || tab[0][0] == '#')
		check = false;
	if (!check_ifdigit(tab[1]) && !check_ifdigit(tab[2]))
		check = false;
	ft_strdel(&tab[0]);
	ft_strdel(&tab[1]);
	ft_strdel(&tab[2]);
	free(tab);
	return (check);
}

/*
** Function : init_room
**------------------------
** @param str : contain name, x & y
** @param room
** @param status 0 = normal, 1 = start, -1 = end
** @param nb_room : which room to init
*/

void		init_room(char *str, t_room **room, int status, int nb_room)
{
	char	**strtab;
	int		i;

	i = 0;
	if (!(strtab = ft_strsplit(str, ' ')))
		exit(0);
	R_STAT(nb_room) = status;
	R_NAME(nb_room) = ft_strdup(strtab[0]);
	R_X(nb_room) = ft_atoi(strtab[1]);
	R_Y(nb_room) = ft_atoi(strtab[2]);
	R_ANT(nb_room) = status == 1 ? true : false;
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
}

/*
** Function : create_rooms
** --------------------------
** @param nb_room : number of rooms to malloc
** @return the malloced struct **
*/

t_room		**create_rooms(int nb_room)
{
	t_room	**room;
	int		i;

	i = 0;
	if (!(room = ft_memalloc((nb_room + 1) * sizeof(t_room *))))
		exit(0);
	while (i < nb_room)
		if (!(room[i++] = ft_memalloc(sizeof(t_room))))
			exit(0);
	return (room);
}
