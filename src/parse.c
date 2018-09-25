/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 22:32:19 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 22:32:19 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		init_room(char *str, t_room **room, int status, int nb_room)
{
	char 	**strtab;
	int 	i;

	i = 0;
	if (!(strtab = ft_strsplit(str, ' ')))
		exit(0);
	R_STAT(nb_room) = status;
	R_NAME(nb_room) = ft_strdup(strtab[0]);
	R_X(nb_room) = ft_atoi(strtab[1]);
	R_Y(nb_room) = ft_atoi(strtab[2]);
	R_ANT(nb_room) = false;
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
}

/*
** Function : fill_room
**-----------------------
** @param tab of the lines we GNLed
** @param ants : number fo ants
** @param nb_room : number of room created
** @param nb : numbers of times the tab of room will be malloc depending on
** NB_MALLOC
** check : 1 = room, 0 = tubes, 2 = start, 3 = end, 4 = comment, 5 = ants
** @return the created tab of room
*/

t_room		**fill_room(char **tab, int *ants, int nb_room, int nb)
{
	t_room	**room;
	int 	s;
	int 	e;
	int 	l;
	int 	check;

	l = 0;
	s = 0;
	e = 0;
	room = realloc_room(NULL, nb);
	while (tab[l] && e < 2 && s < 2 && (check = check_which(tab[l], room)) > 0)
	{
		if (nb_room >= nb * NB_MALLOC && ++nb)
			room = realloc_room(room, nb);
		if (check == 1)
			init_room(tab[l], room, 0, nb_room++);
		else if (check == 2 && check_room(tab[l + 1], room) &&  s++ == 0)
			init_room(tab[++l], room, 1, nb_room++);
		else if (check == 3 && check_room(tab[l + 1], room) && e++ == 0)
			init_room(tab[++l], room, -1, nb_room++);
		else if (check == 5 && *ants == 0)
			*ants = ft_atoi(tab[l]);
		else if (check != 4)
			break;
		l++;
	}
	return (room);
}



/*
** Function fill_tube
**----------------------
** @param tab
** @param room
** @return
*/

t_link		*fill_tubes(char **tab, t_room **room)
{
	t_link		*tube;
	int 		i;
	int 		j;

	j = 0;
	i = get_last_room(room);
	tube = malloc(50);
	while (!ft_strstr(tab[j], R_NAME(i)))
		j++;
	j += 2;
	if (!match(tab[j], "*-*"))
		return (NULL);
	tube = new_list(room[0]);
	return (tube);
}

/*
** Function : create_tab
**-----------------------
** GNL STDOUT until the first free line and cat everything with a '|' in between
** then create a tab with split '|'
** @return the tab
*/

char 		**create_tab()
{
	char 	*line;
	char 	*parsed;
	char 	**tab;
	int 	len;
	int 	nb;

	len = 0;
	nb = 1;
	parsed = ft_strnew(100);
	while (get_next_line(0, &line) == 1 && (len += ft_strlen(line)) && line[0])
	{
		if (++len >= nb * 100 && ++nb)
			parsed = ft_realloc(parsed, (nb - 1) * 100, nb * 100);
		parsed = ft_strcat(ft_strcat(parsed, line), "|");
		ft_strdel(&line);
	}
	if (line)
		free(line);
	tab = ft_strsplit(parsed, '|');
	free(parsed);
	return (tab);
}