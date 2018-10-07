/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solve.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 10:39:03 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 10:39:03 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : is_solve
** -----------------------
** find if there's a start in the tree
** @param root
** @return
*/

bool		is_solve(t_link *root)
{
	int		i;
	bool	check;

	i = 0;
	check = false;
	if (root)
	{
		while (check == false && i < root->nb_kids && root->kids)
		{
			if (root->kids[i])
				check = is_solve(root->kids[i]);
			i++;
		}
		if (check == false && root->room->status == 1)
			return (true);
	}
	return (check);
}

/*
** Function : clean_tree
** @param root
*/

void		clean_tree(t_link **root)
{
	int		i;

	i = 0;
	if (!(*root))
		return ;
	while ((*root)->kids && (*root)->kids[i])
		clean_tree(&(*root)->kids[i++]);
	(*root)->nb_kids = i;
	if (!count_nullkids(*root, i) && (*root)->room->status != 1)
	{
		(*root)->room = NULL;
		ft_memdel((void **)&(*root)->room);
		ft_memdel((void **)&(*root));
	}
}

/*
** Function : send_ant2
** @param root
** @param ants
** @param received
*/

void		send_ant(t_link *root, int *ants, int *received)
{
	int		i;

	i = 0;
	while (i < root->nb_kids && *ants > 0 && !root->room->hantz)
	{
		if (root->kids[i] && root->kids[i]->room->hantz)
		{
			if (!root->room->status)
				root->room->hantz = true;
			if (!root->kids[i]->room->status)
				root->kids[i]->room->hantz = false;
			if (root->kids[i]->room->status == 1)
				*ants -= 1;
			if (root->room->status == -1)
				*received -= 1;
			ft_printf("L%s-%s ", root->kids[i]->room->name, root->room->name);
		}
		i++;
	}
	i = -1;
	while (++i < root->nb_kids && *ants > 0)
	{
		if (root->kids[i])
			send_ant(root->kids[i], ants, received);
	}
}

void		finish_ant(t_link *root, int *received)
{
	int			i;

	i = 0;
	while (i < root->nb_kids && *received > 0)
	{
		if (root->kids[i] && root->kids[i]->room->status == 1)
			root->kids[i]->room->hantz = false;
		if (root->kids[i] && root->kids[i]->room->hantz)
		{
			if (!root->room->status)
				root->room->hantz = true;
			if (root->kids[i]->room->status)
				root->kids[i]->room->hantz = false;
			if (root->room->status == -1)
				*received -= 1;
			ft_printf("L%s-%s ", root->kids[i]->room->name, root->room->name);
		}
		i++;
	}
	i = -1;
	while (++i < root->nb_kids && *received > 0)
	{
		if (root->kids[i])
			finish_ant(root->kids[i], received);
	}
}

/*
** LOL
** @param root
** @param ants
*/

void		solver(t_link *root, int *ants)
{
	int		received;

	received = *ants;
	while (*ants > 0)
	{
		send_ant(root, ants, &received);
		ft_printf("\n");
	}
	while (received > 0)
	{
		finish_ant(root, &received);
		ft_printf("\n");
	}
	if (*ants != 0 || received != 0)
		error("ERROR : problem solver", NULL, NULL, root);
}
