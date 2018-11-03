/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_solver.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/03 06:18:07 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 06:18:07 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : is_solve
**---------------------
** Look for starting room in head
** @param head
** @return : true if starting room found, false if not
*/

bool	is_solve2(t_tube *head)
{
	if (!head)
		return (NULL);
	if (head->room->status == 1)
		return (true);
	if (head->child)
		return (is_solve2(head->child));
	if (head->bro)
		return (is_solve2(head->bro));
	return (false);

}

t_tube	*is_ants(t_tube *node)
{
	if (!node)
		return (NULL);
	if (node->room->hantz)
		return (node);
	if (node->bro)
		return (is_ants(node->bro));
	return (NULL);
}

void 	send_ants2(t_tube *head, int *ants, int *received)
{
	static unsigned int 	nb = 0;
	t_tube					*buf;

	buf = head->child;
	while (*ants && !head->room->hantz && head->child && (buf = is_ants(buf)))
	{
		buf->room->status == 1 ? buf->nb = ++nb : nb; //
		head->room->hantz = !head->room->status ? true : head->room->hantz;
		buf->room->hantz = !buf->room->status ? false : buf->room->hantz;
		ft_swap(&(head->nb), &(buf->nb), sizeof(unsigned int));
		*received = head->room->status == -1 ? *received - 1 : *received;
		*ants = buf->room->status == 1 ? *ants - 1 : *ants;
		ft_printf("L%d-%s ", head->nb, head->room->name);
	}
	if (head->bro)
		send_ants2(head->bro, ants, received);
	if (head->child)
		send_ants2(head->child, ants, received);
}

void 	finish_ants2(t_tube *head, int *received)
{
	t_tube					*buf;

	if (head->child && head->child->room->status == 1)
		head->child->room->hantz = false;
	buf = head->child;
	while (!head->room->hantz && head->child && (buf = is_ants(buf)))
	{
		head->room->hantz = !head->room->status ? true : head->room->hantz;
		buf->room->hantz = !buf->room->status ? false : buf->room->hantz;
		ft_swap(&(head->nb), &(buf->nb), sizeof(unsigned int));
		*received = head->room->status == -1 ? *received - 1 : *received;
		ft_printf("L%d-%s ", head->nb, head->room->name);
	}
	if (head->bro)
		finish_ants2(head->bro, received);
	if (head->child)
		finish_ants2(head->child, received);
}

void	solver(t_tube *head, int *ants)
{
	int 	received;
	t_tube	*buf;

	received = *ants;
	if ((buf = is_ants(head->child)) && buf->room->status == 1)
		exception(head->room->name, ants);
	while (*ants > 0)
	{
		send_ants2(head, ants, &received);
		write(1, "\n", 1);
	}

	while (received > 0)
	{
		finish_ants2(head, &received);
		write(1, "\n", 1);
	}
}