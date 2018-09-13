/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/01 16:55:06 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/01 16:55:06 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int main(void)
{
	t_room	*room = NULL;
	int 	ants;
	char 	*parsed;

	ants = 0;
	parsed = ft_strnew(NB_MALLOC);
	room = ft_parse(&ants, &parsed, 1);
	dprintf(1, "parsed : %s\nants : %d", parsed, ants);
	free(room);
}