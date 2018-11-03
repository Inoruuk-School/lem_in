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


void	free_trie(t_trie **root)
{
	int 	i;

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

void	free_all(char **tab, t_tube **head, t_trie **root)
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

void	error(char *str, char **tab, t_trie **root, t_tube **head)
{
	ft_printf(RED"%s\n"RESET, str);
	free_all(tab, head, root);
	exit(0);
}