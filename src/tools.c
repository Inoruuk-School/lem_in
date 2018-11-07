/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 04:57:21 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 04:57:21 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : free_tube
**----------------------
** @param root : data struct to free
*/

void		free_tube(t_tube **root)
{
	t_tube	*head;

	head = *root;
	if (!head)
		return ;
	if (head->child)
		free_tube(&head->child);
	if (head->bro)
		free_tube(&head->bro);
	if (head->child && !head->child->child)
		del_tube(&head->child);
	if (head->bro && !head->bro->bro)
		del_tube(&head->bro);
	if (head->room->status == -1 && !head->bro && !head->child)
		del_tube(&head);
}

/*
** Function : free_trie
**------------------------
** @param root : trie to free
*/

void		free_trie(t_trie **root)
{
	int		i;

	i = 0;
	while (i < MY_ALPHA)
	{
		if ((*root)->child[i])
			free_trie(&(*root)->child[i]);
		i++;
	}
	if ((*root)->room)
	{
		ft_strdel(&(*root)->room->name);
		ft_memdel((void **)&(*root)->room);
	}
	ft_memdel((void **)&(*root));
}

/*
** Funtion : free_all
**--------------------
** free every param with each associated functions
** @param tab
** @param head
** @param root
*/

void		free_all(char **tab, t_tube **head, t_trie **root)
{
	if (tab)
		free_tab((void **)tab);
	if (head)
		free_tube(head);
	if (root)
		free_trie(root);
}

/*
** Function : error
**------------------
** print str and free the rest of the params
** @param str : error to print
** @param tab : being freed
** @param room : being freed
** @param root : being freed
*/

void		error(char *str, char **tab, t_trie **root, t_tube **head)
{
	ft_printf(RED"%s\n"RESET, str);
	free_all(tab, head, root);
	exit(0);
}

/*
** Function : is_solve
**---------------------
** Look for starting room in head
** @param head
** @return : true if starting room found, false if not
*/

bool		is_solve2(t_tube *head)
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
