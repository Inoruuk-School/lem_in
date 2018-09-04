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
#define LEM_IN_H

# include "def.h"

#include <stdlib.h>
#include <stdio.h>

/*
** Struct t_room
**----------------
** @param : status 0 room normal, -1 room end, +1 room start
** @param : hantz a.k.a ants, s'il y a ou pas une fourmis dans la room, 1 = pleine
** @coord_ : coordonnées x et y de la room
*/

typedef struct	s_room
{
	int			status : 2;
	int			hantz : 1;
	int			coord_x;
	int			coord_y;
	char 		*name;
}				t_room;

/*
** Struct s_tube
**----------------
** @param : nb_tubes nombre de tubes PARTANT de la room
** @param : tubes tableau de room qui sont les chemin disponibles
*/

typedef struct	s_tube
{
	int			nb_tubes;
	t_room		*tubes;
}				t_tube;


#endif