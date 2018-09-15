/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
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

t_room	*realloc_room(t_room *room, int nb)
{
	int			i;
	t_room		*buff;

	nb <= 0 ? nb = 1 : nb;
	i = 0;
	if (room)
	{
		if (!(buff = ft_memalloc(sizeof(t_room) * nb * NB_MALLOC)))
			exit(0);
		buff = ft_memcpy(buff, room, sizeof(t_room) * --nb * NB_MALLOC);
		while (i < nb) //probleme
		{
			dprintf(1, "buff : %s\ni : %d nb : %d\n",buff[i].name, i, nb);
			free(R_NAME(i++));
		}
		free(room);

	}
	else
		if (!(buff = ft_memalloc(sizeof(t_room) * nb * NB_MALLOC)))
			exit(0);
	return (buff);
}

void	aff_room(t_room *room) // a supprimer
{
	int i;

	i = 0;
	while (i < 5)
	{
		dprintf(1, CYN"name : %s\n", R_NAME(i));
		dprintf(1, "status : %d\n", R_STAT(i));
		dprintf(1, "ants : %d\n", R_ANT(i));
		dprintf(1, "x : %d\n", R_X(i));
		dprintf(1, "y : %d\n\n"RESET, R_Y(i));
		i++;
	}
}

void	free_tab(void **tab)
{
	while (*tab)
		ft_memdel(&*tab++);
	free(tab);
}