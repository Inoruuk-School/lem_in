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


void		init_room(char *str, t_room *room, int status, int nb_room)
{
	char 	**strtab;
	int 	i;

	i = 0;
	if (!(strtab = ft_strsplit(str, ' ')))
		exit(0);
	if (check_ifalphanum(strtab[0]) && check_ifdigit(strtab[1]) &&\
		check_ifdigit(strtab[2]) && !strtab[3])
	{
		R_STAT(nb_room) = status;
		R_NAME(nb_room) = ft_strdup(strtab[0]);
		R_X(nb_room) = ft_atoi(strtab[1]);
		R_Y(nb_room) = ft_atoi(strtab[2]);
		R_ANT(nb_room) = false;
	}
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
}

t_room		*fill_room(char **tab, int *ants, int nb_room, int nb)
{
	t_room	*room;
	int 	start;
	int 	end;
	int 	l;
	int 	check;

	l = 0;
	start = 0;
	end = 0;
	room = realloc_room(NULL, sizeof(t_room *) * nb * NB_MALLOC);
	while (tab[l] && end < 2 && start < 2 && (check = check_which(tab[l])) > 0)
	{
		if (nb_room >= nb * NB_MALLOC && ++nb)
		{
			room = realloc_room(room, nb);
		}
		if (check == 1)
			init_room(tab[l], room, 0, nb_room++);
		else if (check == 2 && start++ == 0)
			init_room(tab[++l], room, 1, nb_room++);
		else if (check == 3 && end++ == 0)
			init_room(tab[++l], room, -1, nb_room++);
		else if (check == 5 && *ants == 0)
			*ants = ft_atoi(tab[l]);
		else if (check != 4)
			break;
		l++;
	}
	return (room);
}

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