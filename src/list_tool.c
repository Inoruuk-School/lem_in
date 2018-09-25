/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_tool.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 05:47:06 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 05:47:06 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_link		*new_list(t_room *room)
{
	t_link	*tube;

	if (!(tube = ft_memalloc(sizeof(t_link *))))
		return (0);// peut faire autrement??
	tube->room = room;
	tube->branch = NULL;
	return (tube);
}