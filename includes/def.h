/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   def.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/01 16:56:58 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/01 16:56:58 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

/*
** nombre de room a malloc
*/

# define NB_MALLOC 150

/*
** t_rooms defines
*/

# define R_STAT(i) room[i].status
# define R_ANT(i) room[i].hantz
# define R_Y(i) room[i].coord_y
# define R_X(i) room[i].coord_x
# define R_NAME(i) room[i].name

/*
** t_tube defines
*/

# define L_NB link->nb_tubes
# define L_TUBE(i) link->tubes[i]

#endif
