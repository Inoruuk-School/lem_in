/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clean_tube.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/03 05:45:21 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 05:45:21 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : del_tube
**--------------------
** @param head : node to delete
** @return
*/

t_tube		*del_tube(t_tube **head)
{
	t_tube	*buf;

	buf = NULL;
	if ((*head)->bro)
		buf = (*head)->bro;
	ft_memdel((void **)&(*head));
	return (buf);
}

/*
** Function : clean_tube
**-------------------------
** check to see if each paths lead to the starting room,
** when the stating room is found, check the brothers of the node before the SR
** to see if one of them is the SR for a shorter path
** @param head : data struct to clean
*/

void		clean_tube(t_tube **head)
{
	if ((*head)->bro)
		clean_tube(&(*head)->bro);
	if ((*head)->child)
		clean_tube(&(*head)->child);
	if (!(*head)->child && (*head)->room->status != 1)
		*head = del_tube(&(*head));
	if ((*head) && (*head)->child && (*head)->bro && \
		(*head)->child->room->status == 1 && check_bro_status(*head))
	{
		(*head)->child = del_tube(&(*head)->child);
		*head = del_tube(&(*head));
	}
}

/*
** Function : check_bro_status
**------------------------------
** Look for the starting room in the node's brothers
** @param node to check
** @return true if the starting room is found in the brothers, false if not
*/

bool		check_bro_status(t_tube *node)
{
	if (node->bro)
		return (check_bro_status(node->bro));
	if (node->room->status == 1)
		return (true);
	return (false);
}

/*
** Function : find_links
**-----------------------
** Search in tab which line is the first links
** @param tab
** @return : first line where the links are
*/

char		**find_links(char **tab)
{
	while (*tab && !match(*tab, "*-*"))
		tab++;
	return (tab);
}
