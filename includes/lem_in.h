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
** Struct s_link
**----------------
**
*/

typedef struct	s_link
{
	t_room				*room;
	struct	s_link		*bro;
	void				*child;
}				t_link;

bool		check_ifdigit(char *to_check);
bool		check_ifalphanum(char *to_check);
t_room		*ft_parse(int *ants, char **parsed, int nb);
t_room		**realloc_room(t_room **room, int nb);
void		aff_room(t_room **room, int nb_room);
void		error(int er);
int			check_parse(char **tab, int *ants);
int 		get_last_room(t_room **room);

void		free_all(t_room ***room, char ***tab);
void 		error(int er);
t_link		*new_list(t_room *room);
t_link		*fill_tubes(char **tab, t_room **room);

/*
** parse_room
*/

int 		check_first_step(char** tab, int *ants);
char 		**create_tab();
t_room		**fill_room(char **tab, int nb_room);
bool		check_rooms(t_room **room, int nb_room);

/*
* room_tool
*/

bool		check_room(char *str);
void		init_room(char *str, t_room **room, int status, int nb_room);
char	 	**next_tab(char **tab);
t_room		**create_rooms(int nb_room);
int 		check_which(char *str);

#endif
