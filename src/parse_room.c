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
** Function : fill_room
**-----------------------
** i : -1 = end, 0 = room, 1 = start, 3 = tubes, 4 = comment, 5 = ants
** create the rooms and the trie
** @param tab of the lines we GNLed
** @return the trie
*/

t_trie		*fill_room(char **tab)
{
	t_trie	*root;
	char	**buff;
	int		i;

	buff = tab++;
	if (!(root = getnode()))
		return (NULL);
	while (*tab)
	{
		i = check_which(*tab);
		if ((i == 1 || i == -1) && (tab = next_tab(tab)))
			init_room(*tab, i, root, buff);
		else if (!i)
			init_room(*tab, i, root, buff);
		else if (i != 4)
			break ;
		tab++;
	}
	return (root);
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
	if (line && len)
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
** i : -1 = start, 0 = room, 1 = end, 3 = tubes, 4 = comment, 5 = ants
** @param tab
** @param ants
** @return the number of rooms or -1 if the first half of parsing is bad
*/

bool		check_first_step(char **tab, int *ants)
{
	int		end;
	int		start;
	int		i;

	end = 0;
	start = 0;
	if ((i = check_which(*tab)) != 5)
		return (-1);
	*ants = ft_atoi(*tab++);
	while (*tab)
	{
		i = check_which(*tab);
		if (i == -1)
			start++;
		else if (i == 1)
			end++;
		else if (i == 5)
			i = -1;
		else if (i != 4 && i != 0)
			break ;
		tab++;
	}
	return ((end != 1 || start != 1 || i == -1) ? false : true);
}
