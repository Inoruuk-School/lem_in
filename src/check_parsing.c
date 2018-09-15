/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_parsing.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/08 17:20:58 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/08 17:20:58 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	check_tubes(char **tab, int *line)
{
	(void)tab;
	(void)line;
	return (-1);
}

bool	check_room(char *str)
{
	char 	**tab;
	bool	check;

	check = true;
	if (!(tab = ft_strsplit(str, ' ')))
		exit(0);
	if (!check_ifalphanum(tab[0]) && tab[0][0] != 'L' && tab[0][0] != '#')
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
** Function check_which
**---------------------
** @param str given string to check
** @return 1 = room, 0 = tubes, 2 = start, 3 = end, 4 = comment, 5 = ants
*/

int 	check_which(char *str)
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
