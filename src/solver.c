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
** Function : exception
**-----------------------
** Used only when start and end are linked
** @param end
** @param ants
*/

void		exception(char *end, int *ants)
{
	int i;
	int nb;

	i = 1;
	nb = *ants;
	while (nb > 0)
	{
		ft_printf("L%d-%s ", i++, end);
		nb--;
	}
	write(0, "\n", 1);
	*ants = nb;
}

/*
** Function : is_ants
**--------------------
** search for ants in this node and it's brothers
** @param node
** @return
*/

t_tube		*is_ants(t_tube *node)
{
	if (!node)
		return (NULL);
	if (node->room->hantz)
		return (node);
	if (node->bro)
		return (is_ants(node->bro));
	return (NULL);
}

/*
** Function : send_ants
**--------------------
** Start pushing ants to the ending room, when there are no more ants to send
** stop send_ants and start finish_ants
** @param head
** @param ants
** @param received
*/

void		send_ants(t_tube *head, int *ants, int *received)
{
	static unsigned	int		nb = 0;
	t_tube					*buf;

	buf = head->child;
	while (*ants && !head->room->hantz && head->child && (buf = is_ants(buf)))
	{
		buf->room->status == 1 ? buf->nb = ++nb : nb;
		head->room->hantz = !head->room->status ? true : head->room->hantz;
		buf->room->hantz = !buf->room->status ? false : buf->room->hantz;
		ft_swap(&(head->nb), &(buf->nb), sizeof(unsigned int));
		*received = head->room->status == -1 ? *received - 1 : *received;
		*ants = buf->room->status == 1 ? *ants - 1 : *ants;
		if (buf->room->status == 1)
			ft_printf(GRN"L%d-%s "RESET, head->nb, head->room->name);
		else if (head->room->status == -1)
			ft_printf(YEL"L%d-%s "RESET, head->nb, head->room->name);
		else
			ft_printf(RESET"L%d-%s ", head->nb, head->room->name);
	}
	if (head->bro)
		send_ants(head->bro, ants, received);
	if (head->child)
		send_ants(head->child, ants, received);
}

/*
** Function : finish_ants
**------------------------
** Push the remaining ants to the ending room
** @param head
** @param received
*/

void		finish_ants(t_tube *head, int *received)
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
		if (head->room->status == -1)
			ft_printf(YEL"L%d-%s "RESET, head->nb, head->room->name);
		else
			ft_printf(RESET"L%d-%s ", head->nb, head->room->name);
	}
	if (head->bro)
		finish_ants(head->bro, received);
	if (head->child)
		finish_ants(head->child, received);
}

/*
** Function : solver
**------------------
** First : look if the starting room is next to the ending room
** if so -> exception, if not send every ants, then finish sending them
** @param head
** @param ants
*/

void		solver(t_tube *head, int *ants)
{
	int		received;
	t_tube	*buf;

	received = *ants;
	if ((buf = is_ants(head->child)) && buf->room->status == 1)
		exception(head->room->name, ants);
	else
	{
		while (*ants > 0)
		{
			send_ants(head, ants, &received);
			write(1, "\n", 1);
		}
		while (received > 0)
		{
			finish_ants(head, &received);
			write(1, "\n", 1);
		}
	}
}
