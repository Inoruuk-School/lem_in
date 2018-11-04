/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   trie.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/27 02:54:40 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/27 02:54:40 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : find_key
**----------------------
** key is the position in the following string :
** "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
** @param c : needed to find key
** @return the key
*/

int			find_key(char c)
{
	int		key;

	key = -1;
	if (ft_ismin(c))
		key = c - 'a';
	else if (ft_iscap(c))
		key = 26 + c - 'A';
	else if (ft_isdigit(c))
		key = 52 + c - '0';
	return (key);
}

/*
** Function : getnode
** ----------------------
** Create a fresh, null node needed for the rooms
** @return : node or null if node failed to be created
*/

t_trie		*getnode(void)
{
	t_trie		*node;

	if (!(node = (t_trie *)ft_memalloc(sizeof(t_trie))))
		return (NULL);
	return (node);
}

/*
** function : put_room
**-----------------------
** Find duplicates room and create the path with the name for easy location
** @param root : trie to brows through
** @param room :room to put in a certain position depending on it's name
** @param name : the name of the room
*/

void		put_room(t_trie *root, t_room *room, char *name)
{
	int		key;

	if (!*name && !root->room)
	{
		root->room = room;
		return ;
	}
	if (!*name && root->room)
		error("ERROR : duplicate rooms", NULL, NULL, NULL);
	key = find_key(*name++);
	if (!root->child[key])
	{
		if (!(root->child[key] = getnode()))
			exit(2);
		put_room(root->child[key], room, name);
	}
	else if (root->child[key])
		put_room(root->child[key], room, name);
}

/*
**Function : getroom
**--------------------
** in root search of the room whose name is str
** @param root
** @param str
** @return
*/

t_room		*getroom(t_trie *root, char *str)
{
	int		key;

	if (!root || !str)
		return (NULL);
	while (*str)
	{
		key = find_key(*str);
		if (root->child[key])
			root = root->child[key];
		str++;
	}
	if (root && root->room)
		return (root->room);
	return (NULL);
}

/*
** Function : aff_trie
**--------------------
** print the name of every rooms in the trie
** MY_APLHA : size of my used alphabet, countains alphanums char
** @param root
*/

void		aff_trie(t_trie *root)
{
	int		i;

	i = 0;
	while (i < MY_ALPHA)
	{
		if (root->child[i])
			aff_trie(root->child[i]);
		i++;
	}
	if (root->room)
		dprintf(1, "%s\n", root->room->name);
}
