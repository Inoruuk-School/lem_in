/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-NB_MALLOC1.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 22:16:05 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 22:16:05 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

bool	check_ifdigit(char *to_check)
{
	bool	check;

	check = true;
	while (*to_check && check)
	{
		if (!isdigit(*to_check++))
			check = false;
	}
	return (check);
}

bool	check_ifalphanum(char *to_check)
{
	int		i;
	bool	check;

	i = 0;
	check = true;
	while (check && to_check[i] != '\0')
	{
		if (!isalnum(to_check[i]))
			check = false;
		i++;
	}
	return (check);
}

t_room	*copy_room(t_room *buff, t_room *room)
{
	if (!buff || !room)
		return (NULL);
	buff->name = ft_strdup(room->name);
	buff->coord_x = room->coord_x;
	buff->coord_y = room->coord_y;
	buff->status = room->status;
	buff->hantz = room->hantz;
	return (buff);
}

t_room	**realloc_room(t_room **room, int nb)
{
	int			i;
	t_room		**buff;

	nb <= 0 ? nb = 1 : nb;
	i = 0;
	if (room)
	{
		if (!(buff = ft_memalloc(sizeof(t_room *) * (nb + 1) * NB_MALLOC)))
			exit(0);
		while (i < nb * NB_MALLOC)
			if (!(buff[i++] = ft_memalloc(sizeof(t_room))))
				exit(0);
		i = -1;
		while (room[++i])
			if (!(buff[i] = copy_room(buff[i], room[i])))
				exit(0);
		free_all(&room, NULL);
	}
	else
	{
		if (!(buff = ft_memalloc((1 + nb) * NB_MALLOC * sizeof(t_room *))))
			exit(0);
		while (i < nb * NB_MALLOC)
			if (!(buff[i++] = ft_memalloc(sizeof(t_room))))
				exit(0);
	}
	return (buff);
}

int		get_last_room(t_room **room)
{
	int 	i;

	i = 0;
	while (room[i])
	{
		if (room[i + 1])
			i++;
		else
			break;
	}
	return (i);
}

void	aff_room(t_room **room) // a supprimer
{
	int i;

	i = 0;
	if (room)
	{
		while (room[i] && R_NAME(i))
		{
			dprintf(1, CYN"name : %s\n", R_NAME(i));
			dprintf(1, "status : %d\n", R_STAT(i));
			dprintf(1, "ants : %d\n", R_ANT(i));
			dprintf(1, "x : %d\n", R_X(i));
			dprintf(1, "y : %d\n\n"RESET, R_Y(i));
			i++;
		}
	}
}
