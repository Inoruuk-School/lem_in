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
	int		i;
	bool	check;

	i = 0;
	check = true;
	while (check && to_check[i] != '\0')
	{
		if (!isdigit(to_check[i]))
			check = false;
		i++;
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

	i = 0;
	nb <= 0 ? nb = 1 : nb;
	if (room)
	{
		if (!(buff = (t_room *)malloc(sizeof(t_room) * nb * NB_MALLOC)))
			exit(0);
		nb = nb <= 1 ? 1 : nb - 1;
		ft_memcpy(buff, room, sizeof(t_room) * nb * NB_MALLOC);
		while (i < nb * NB_MALLOC && R_NAME(i))
		{
			free(R_NAME(i));
			i++;
		}
		free(room);
	}
	else
		if (!(buff = (t_room *) malloc(sizeof(t_room) * nb * NB_MALLOC)))
			exit(0);
	return (buff);
}

void	aff_room(t_room *room, int nb_room) // a changer pour l affichage
{
	int i = 0;

	while (i < nb_room)
	{
		dprintf(1, "name : %s\n", R_NAME(i));
		dprintf(1, "status : %d\n", R_STAT(i));
		dprintf(1, "ants : %d\n", R_ANT(i));
		dprintf(1, "x : %d\n", R_X(i));
		dprintf(1, "y : %d\n\n", R_Y(i));
		i++;
	}
}

void	free_tab(void	**tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}