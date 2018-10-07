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
** t_rooms defines
*/

# define R_STAT(i) room[i]->status
# define R_ANT(i) room[i]->hantz
# define R_Y(i) room[i]->coord_y
# define R_X(i) room[i]->coord_x
# define R_NAME(i) room[i]->name

/*
** t_link defines
*/

# define L_STAT tube->room->status
# define L_ANT tube->room->hantz
# define L_Y tube->room->coord_y
# define L_X tube->room->coord_x
# define L_NAME tube->room->name

#endif
