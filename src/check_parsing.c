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

bool	check_room(char *str, int i)
{
	char	*tmp;
	bool	check;

	check = true;
	tmp = ft_strdup(str);
	while (str[i] && str[i] != ' ')
		i++;
	tmp[i] = '\0';
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	tmp[i] = '\0';
	if (!check_ifalphanum(tmp) && (i = 0) == 0)
		check = false;
	while (tmp[i])
		i++;
	if (!check_ifdigit(&tmp[++i]))
		check = false;
	while (tmp[i])
		i++;
	if (!check_ifdigit(&tmp[++i]))
		check = false;
	free(tmp);
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
	if (match(str, "* * *") && check_room(str, 0))
		return (1);
	else if (match(str, "*-*"))
		return (0);
	else if (str[0] == '#' && ft_strstr(str, "##start"))
		return (2);
	else if (str[0] == '#' && ft_strstr(str, "##end"))
		return (3);
	else if (str[0] == '#')
		return (4);
	else if (check_ifdigit(str))
		return (5);
	return (-1);
}
