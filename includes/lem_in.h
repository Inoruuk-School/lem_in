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

# define MY_ALPHA 62

/*
** Struct t_room
**----------------
** @param : status 0 room normal, -1 room end, +1 room start
** @param : hantz a.k.a ants, 0 = vide 1 = plein
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
** Struct t_trie
**----------------
** tree struct used to organize and search easily the rooms by their name
*/

typedef struct		s_trie
{
	struct s_trie	*child[62];
	t_room			*room;
}					t_trie;

/*
** Struct_t_tube
**----------------
** tree with unknow numbers of children for each nodes
** first child is create and the others children are put in this child's bro
*/

typedef struct		s_tube
{
	unsigned int	nb;
	t_room			*room;
	struct s_tube	*bro;
	struct s_tube	*child;
}					t_tube;

void				aff_tab(char **tab);

/*
** parse_room.c
*/

bool				check_first_step(char **tab, int *ants);
char				**create_tab(void);
t_trie				*fill_room(char **tab);

/*
** room_tool.c
*/

bool				check_room(char *str);
char				**next_tab(char **tab);
int					check_which(char *str);
void				init_room(char *str, int status, t_trie *root, char **tab);

/*
** trie.c
*/

t_trie				*getnode(void);
t_room				*getroom(t_trie *root, char *str);
int					find_key(char c);
void				put_room(t_trie *root, t_room *room, char *name);
void				aff_trie(t_trie *root);

/*
** tools.c
*/

bool				is_solve2(t_tube *head);
void				free_tube(t_tube **head);
void				error(char *str, char **tab, t_trie **root, t_tube **head);
void				free_trie(t_trie **root);
void				free_all(char **tab, t_tube **head, t_trie **root);

/*
** tube.c
*/
char				*find_end(char **tab);
t_tube				*getlinks(t_tube *head, t_trie *root, char **tab, char *s);
t_tube				*getend(t_trie *root, char **tab, char *end);
void				gittubes(t_tube *head, t_trie *root, char **tab);
t_tube				*parse_tubes(char **tab, t_trie *root, char *end);

/*
** tube_tool.c
*/

t_tube				*make_tube(t_room *room);
void				make_bro(t_tube *current, t_room *room);
void				check_links(char **tab, t_trie *root);
bool				check_name3(char *str, t_trie *root);
void				del_dup_link(char **split);
/*
** clean_tube.c
*/

void				clean_tube(t_tube	**head);
t_tube				*del_tube(t_tube **head);
bool				check_bro_status(t_tube *node);
char				**find_links(char **tab);

/*
** solver.c
*/

void				exception(char *end, int *ants);
t_tube				*is_ants(t_tube *node);
void				send_ants(t_tube *head, int *ants, int *received);
void				finish_ants(t_tube *head, int *received);
void				solver(t_tube *head, int *ants);

#endif
