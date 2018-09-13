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
	int		i;

	if (!(strtab = ft_strsplit(str, ' ')))
		exit(0);
	i = 0;
	if (check_ifalphanum(strtab[0]) && check_ifdigit(strtab[1]) &&\
		check_ifdigit(strtab[2]) && !strtab[3])
	{
		R_STAT(nb_room) = status;
		R_NAME(nb_room) = ft_strdup(strtab[0]);
		R_X(nb_room) = ft_atoi(strtab[1]);
		R_Y(nb_room) = ft_atoi(strtab[2]);
		R_ANT(nb_room) = false;
	}
	free_tab(strtab);
}

int			fill_room(char **tab, t_room *room, int *ants, int nb_room)
{
	int 	start;
	int 	end;
	int 	line;
	int 	check;

	line = 0;
	start = 0;
	end = 0;
	while (tab[line] && end <= 1 && start <= 1 && (check = check_which(tab[line])) > 0)
	{
		if (check == 1)
			init_room(tab[line], room, 0, nb_room++);
		else if (check == 2 && start++ == 0)
			init_room(tab[++line], room, 1, nb_room++);
		else if (check == 3 && end++ == 0)
			init_room(tab[++line], room, -1, nb_room++);
		else if (check == 5 && *ants == 0)
			*ants = ft_atoi(tab[line]);
		else if (check != 4)
			break;
		line++;
	}
	return (line);
}

t_room		*ft_parse(int *ants, char **parsed, int nb) // a faire le tube apres fill-room
{
	char	*line;
	char 	**tab;
	int		i;
	int 	len;
	t_room	*room;

	len = 0;
	room = realloc_room(NULL, 1);
	while (get_next_line(0, &line) == 1 && (len += ft_strlen(line)) && line[0])
	{
		if (++len >= nb * NB_MALLOC && (nb += 1))
			*parsed = ft_realloc(*parsed, (nb - 1) * NB_MALLOC, nb * NB_MALLOC);
		*parsed = ft_strcat(ft_strcat(*parsed, line), "|");
		ft_strdel(&line);
	}
	parsed[0][len - 1] = '\0';
	tab = ft_strsplit(*parsed, '|');
	i = fill_room(tab, room, ants, 0);
	free_tab(tab);
	return (room);
}
