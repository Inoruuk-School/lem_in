/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_tube.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/28 01:20:39 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/28 01:20:39 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function : find_end
**-----------------------
** find the ending room in tab
** @param tab
** @return
*/

char 		*find_end(char **tab)
{
	while (*tab)
	{
		if (tab[0][0] == '#' && tab[0][1] == '#' && !ft_strcmp(*tab, "##end"))
			break ;
		tab++;
	}
	return (*next_tab(tab));
}



/*
** Function : getlinks
**---------------------
** First : search for a link
** Second : create a child if the current tube doesn't have one
** Third : if there's a new link and the tube have a child already, create this
** 			child's brother
** @param head
** @param root
** @param tab
** @param str
** @return
*/

t_tube		*getlinks(t_tube *head, t_trie *root, char **tab, char *str)
{
	char 		*buff;

	while (*tab)
	{
		buff = NULL;
		if (**tab && (buff = ft_strstr(*tab, str)))
		{
			if ((buff = ft_strchr(*tab, '-')))
				tab[0][buff++ - *tab] = '\0';
			buff = !strcmp(buff, str) ? *tab : buff;
		}
		if (buff)
		{
			if (!head->child)
				head->child = make_tube(getroom(root, buff));
			else if (head->child)
				make_bro(head->child, getroom(root, buff));
			**tab = '\0';
		}
		tab++;
	}
	return (head);
}

/*
** Function : getend
**-------------------
** make the root of the path_tree used to push ants
** @param root
** @param tab
** @param end
** @return
*/

t_tube		*getend(t_trie *root, char **tab, char *end)
{
	t_room		*endroom;
	t_tube		*head;
	char 		*buff;

	buff = ft_strchr(end, ' ');
	*buff = '\0';
	endroom = getroom(root, end);
	head = make_tube(endroom);
	if (!head)
		return (NULL);
	head = getlinks(head, root, tab, endroom->name);
	(void)tab;
	return (head);
}

/*
** Function : gittubes
**---------------------
** create the tree of path with the tab of links
** @param root : full of rooms
** @param tab : full of links
** @return the created tree of links
*/

void		gittubes(t_tube *head, t_trie *root, char **tab)
{
	if (!head->child && head->room->status != 1)
		getlinks(head, root, tab++, head->room->name);
	if (head->bro)
		gittubes(head->bro, root, tab);
	if (head->child)
		gittubes(head->child, root, tab);
}

/*
** Function parse_tube
** -------------------
** WHY tab + 6 ? There's at least 1 line for the ants, 4 for start and end
** and a link, which make it 6
** @param tab
** @param room
** @return
*/

t_tube		*parse_tubes(char **tab, t_trie *root)
{
	char		**cpy;
	char 		**buff;
	char 		*end;
	t_tube		*head;

	cpy = tab;
	end = find_end(tab);
	tab += 5;
	while (*tab && !match(*tab, "*-*"))
		tab++;
	check_links(tab, root);
	if (!*tab || !**tab)
		error("ERROR: link error", cpy, NULL, NULL);
	cpy = copy_tab(tab);
	buff = cpy;
	duplicate_link(cpy);
	head = getend(root, cpy, end);
	if (!head)
		error("ERROR: tube making error", cpy, NULL, NULL);
	while (*cpy)
	{
		if (**cpy)
			gittubes(head, root, cpy);
		cpy++;
	}
	clean_tube(&head);
	free_tab((void **)buff);
	return (head);
}