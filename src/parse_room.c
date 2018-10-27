/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 22:32:19 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 22:32:19 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : check_rooms
**---------------------------
** check the names of rooms to see if there is no duplicate
** @param room
** @param nb_room
** @return
*/

bool		check_duplicate_rooms(t_room **room, int nb_room)
{
	bool	check;
	int		i;
	int		j;

	i = 0;
	check = true;
	while (i < nb_room && check)
	{
		j = i + 1;
		while (j < nb_room && check)
		{
			if (!ft_strcmp(R_NAME(i), R_NAME(j)))
				check = false;
			j++;
		}
		i++;
	}
	return (check);
}

/*
** Function : fill_room
**-----------------------
** @param tab of the lines we GNLed
** @param nb_room : number of room created
** i : 0 = tubes,1 = room, 2 = start, 3 = end, 4 = comment, 5 = ants
** @return the created tab of room
*/

t_list		*fill_room(char **tab, int nb_rooms)
{
	t_list	*list;
	t_list	*head;
	int		i;

	i = 0;
	if (!(list = ft_lstnew(NULL, 0)))
		return (NULL);
	head = list;
	while (*tab && (i = check_which(*tab)))
	{
		if (i == 1)
			list->content = init_room2(*tab, 0);
		else if (i == 2 && (tab = next_tab(tab)))
			init_room(*tab, room, 1, --nb_rooms);
		else if (i == 3 && (tab = next_tab(tab)))
			init_room(*tab, room, -1, --nb_rooms);
		else if (i != 4 && i != 5)
			break ;
		tab++;
	}
	return (head);
}

/*
** Function : create_tab
**-----------------------
** GNL STDOUT until the first free line and cat everything with a '|' in between
** then create a tab with split '|'
** @return the tab
*/

char		**create_tab(void)
{
	char	*line;
	char	*parsed;
	char	**tab;
	int		len;
	int		nb;

	len = 0;
	nb = 1;
	parsed = ft_strnew(100);
	while (get_next_line(0, &line) == 1 && (len += ft_strlen(line)) && line[0])
	{
		if (++len >= nb * 100 && ++nb)
			parsed = ft_realloc(parsed, (nb - 1) * 100, nb * 100);
		parsed = ft_strcat(ft_strcat(parsed, line), "|");
		ft_strdel(&line);
	}
	if (line)
		free(line);
	tab = ft_strsplit(parsed, '|');
	free(parsed);
	if (!*tab)
		error("ERROR : FEeeEED ME LINES PLZ!\n", tab, NULL, NULL);
	return (tab);
}

/*
** Function : check_first_step
**-----------------------------
** check if there is a good number of commands and rooms and ants
** @param tab
** @param ants
** @return the number of rooms or -1 if the first half of parsing is bad
*/

int			check_first_step(char **tab, int *ants, int start)
{
	int		end;
	int		nb_room;
	int		i;

	nb_room = 0;
	end = 0;
	if ((i = check_which(*tab)) != 5)
		return (-1);
	*ants = ft_atoi(*tab++);
	while (i != -1 && *tab && (i = check_which(*tab)))
	{
		if (i == 1)
			nb_room++;
		else if (i == 2)
			start++;
		else if (i == 3)
			end++;
		else if (i == 5)
			i = -1;
		else if (i != 4)
			break ;
		tab++;
	}
	return ((end != 1 || start != 1 || i == -1) ? -1 : nb_room);
}

