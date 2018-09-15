/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/31 11:08:15 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 11:08:15 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include "def.h"
# include <stdbool.h>

# include <stdlib.h>
# include <stdio.h>

/*
** Struct t_room
**----------------
** @param : status 0 room normal, -1 room end, +1 room start
** @param : hantz a.k.a ants, 0 = vide 1 = plein
** @coord_ : coordonnées x et y de la room
*/

typedef struct	s_room
{
	int			status : 2;
	bool		hantz;
	int			coord_x;
	int			coord_y;
	char		*name;
}				t_room;

/*
** Struct s_tube
**----------------
** @param : nb_tubes nombre de tubes PARTANT de la room
** @param : tubes tableau de room qui sont les chemin disponibles
*/

typedef struct	s_link
{
	int			nb_tubes;
	t_room		*tubes;
}				t_link;

bool	check_ifdigit(char *to_check);
bool	check_ifalphanum(char *to_check);
int 	check_which(char *str);
t_room	*ft_parse(int *ants, char **parsed, int nb);
t_room	*realloc_room(t_room *room, int nb);
void	aff_room(t_room *room);
void	free_tab(void **tab);
void	error(int er);
int		check_parse(char **tab, int *ants);

t_room		*fill_room(char **tab, int *ants, int nb_room, int nb);
char 		**create_tab();

#endif
