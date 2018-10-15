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
	if (!count_nullkids(*root, i) && (!(*root)->room ||\
		(*root)->room->status != 1))
	{
		(*root)->room = NULL;
		ft_memdel((void **)&(*root)->room);
		ft_memdel((void **)&(*root));
	}
}

/*
** Function : send_ant
** @param root
** @param ants
** @param received
*/

void		send_ant(t_link *root, int *ants, int *received, int i)
{
	static int		nb = 1;

	while (i < root->nb_kids && *ants > 0 && !root->room->hantz)
	{
		if (root->kids[i] && root->kids[i]->room->hantz)
		{
			if (root->kids[i]->room->status == 1)
				root->kids[i]->number = nb++;
			ft_swap(&(root->kids[i]->number), &(root->number), sizeof(int));
			if (!root->room->status)
				root->room->hantz = true;
			if (!root->kids[i]->room->status)
				root->kids[i]->room->hantz = false;
			if (root->kids[i]->room->status == 1)
				*ants -= 1;
			if (root->room->status == -1)
				*received -= 1;
			ft_printf("L%d-%s ", root->number, root->room->name);
		}
		i++;
	}
	i = -1;
	while (++i < root->nb_kids && *ants > 0)
		if (root->kids[i])
			send_ant(root->kids[i], ants, received, 0);
}

void		finish_ant(t_link *root, int *received, int i)
{
	while (i < root->nb_kids && *received > 0 && !root->room->hantz)
	{
		if (root->kids[i] && root->kids[i]->room->status == 1)
			root->kids[i]->room->hantz = false;
		if (root->kids[i] && root->kids[i]->room->hantz)
		{
			ft_swap(&(root->kids[i]->number), &(root->number), sizeof(int));
			if (!root->room->status)
				root->room->hantz = true;
			if (root->kids[i]->room->status == 0)
				root->kids[i]->room->hantz = false;
			if (root->room->status == -1)
				*received -= 1;
			ft_printf("L%d-%s ", root->number, root->room->name);
		}
		i++;
	}
	i = -1;
	while (++i < root->nb_kids && *received > 0)
	{
		if (root->kids[i])
			finish_ant(root->kids[i], received, 0);
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
		send_ant(root, ants, &received, 0);
		ft_printf("\n");
	}
	while (received > 0)
	{
		finish_ant(root, &received, 0);
		ft_printf("\n");
	}
	if (*ants != 0 || received != 0)
		error("ERROR : problem solver", NULL, NULL, root);
}
