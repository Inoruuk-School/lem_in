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
** Function : search_links
**--------------------------
** Search every link with the room "name" in tab
** @param tab
** @param name
** @param nb_rooms
** @return
*/
/*
char		**search_links(char **tab, char *name, int nb_rooms)
{
	char	**split;
	char	*buff;
	void	*start;

	if (!(split = ft_memalloc(sizeof(char *) * (nb_rooms + 1))))
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
	return (start);
}
*/