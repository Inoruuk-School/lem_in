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

/*
** Struct t_room
**----------------
** @param : status 0 room normal, -1 room end, +1 room start
** @param : hantz a.k.a ants, 0 = vide 1 = plein
** @coord_ : coordonnées x et y de la room
*/

typedef struct		s_room
{
	int				status : 2;
	bool			hantz;
	int				coord_x;
	int				coord_y;
	char			*name;
}					t_room;

/*
** Struct s_link
*/

typedef struct		s_link
{
	int				nb_kids;
	int				number;
	t_room			*room;
	struct s_link	**kids;
}					t_link;

/*
** main
*/

void				error(char *str, char **tab, t_room **room, t_link *root);
void				exeption(t_link *end, int *ants);

/*
** parse_room.c
*/

int					check_first_step(char **tab, int *ants, int start);
char				**create_tab(void);
t_room				**fill_room(char **tab, int nb_room);
bool				check_duplicate_rooms(t_room **room, int nb_room);

/*
** room_tool.c
*/

bool				check_room(char *str);
void				init_room(char *str, t_room **room, int stat, int nb_room);
char				**next_tab(char **tab);
t_room				**create_rooms(int nb_room);
int					check_which(char *str);

/*
** tube_parse.c
*/

t_link				*fill_tubes(char **tab, t_room **room, int nb_room);
t_link				*create_root(t_room *room);

/*
** tube_tools.c && tube_tools2.c
*/

t_room				*search_end(t_room **room);
char				**search_links(char **tab, char *name, int nb_rooms);
char				**check_duplicate(char **split);
bool				check_name2(char *str, t_room **room);
int					count_split(char **split);
t_link				**create_kids(char **split, int nb, t_room **room);
void				init_kids(t_link **kids, char **split, t_room **room);
t_room				*search_room(t_room **room, char *name);
void				path(t_link *root, char **tab, t_room **room, int nb);

/*
** solve.c
*/

void				clean_tree(t_link **root);
bool				is_solve(t_link *root);
void				solver(t_link *root, int *ants);

/*
** tools.c
*/

void				free_all(t_room **room, char **tab, t_link *head);
void				free_room(t_room ***room);
void				free_link(t_link *root);
void				aff_tab(char **tab);
int					count_nullkids(t_link *root, int nb);

#endif
