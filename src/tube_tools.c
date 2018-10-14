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
** Function : search_end
**------------------------
** Search the room with status -1, which is the last room
** @param room : tab of room to search from
** @return the name of the end room
*/

t_room		*search_end(t_room **room)
{
	if (room)
	{
		while (*room)
		{
			if ((*room)->status == -1)
				break ;
			room++;
		}
	}
	return (*room);
}

/*
** Function : create_root
**---------------------------
** Init the root with the last room of the amthill
** @param room
** @return
*/

t_link		*create_root(t_room *room)
{
	t_link		*root;

	root = NULL;
	if (room)
	{
		root = ft_memalloc(sizeof(t_link));
		root->room = room;
		root->room->hantz = false;
		root->kids = NULL;
	}
	return (root);
}

/*
** Function : check_duplicates
**------------------------------
** check duplicates in split ?!?!
** @param split
** @return : split
*/

char		**check_duplicate(char **split)
{
	int i;
	int j;

	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		while (split[i] && !split[i][0])
			i++;
		j = i + 1;
		while (split[j])
		{
			if (strcmp(split[i], split[j]) == 0)
				split[j][0] = '\0';
			j++;
		}
		i++;
	}
	return (split);
}

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

/*
** Function : init_kids
** @param kids
** @param split
** @param room
*/

void		init_kids(t_link **kids, char **split, t_room **room)
{
	t_room	*r2;

	if (!kids || !split || !room)
		exit(0);
	while (*split)
	{
		if (**split != '\0')
		{
			r2 = search_room(room, *split);
			(*kids)->room = r2;
			kids++;
		}
		split++;
	}
}
