/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tube_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 06:09:27 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 06:09:27 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : check_name
** --------------------------
** check if the room names given in str exist in room
** @param str : tube to check, 2 names in tubes separated by '-'
** @param room : where the names to compares are
** @return true if the 2 rooms exist
*/

bool		check_name2(char *str, t_room **room)
{
	char	*str2;
	bool	first;
	bool	sec;

	first = true;
	sec = true;
	str2 = 1 + ft_strchr(str, '-');
	str[str2 - str - 1] = '\0';
	while (*room && (first || sec))
	{
		if (first && !ft_strcmp((*room)->name, str))
			first = false;
		else if (sec && ft_strcmp(str2, (*room)->name) == 0)
			sec = false;
		room++;
	}
	str[str2 - str - 1] = '-';
	return (!first && !sec ? true : false);
}

