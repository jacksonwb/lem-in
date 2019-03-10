/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_solver_helper2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:20:38 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/08 12:00:24 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "flow_solver.h"

int		queue_contains(t_queue *q, int room_id)
{
	t_elem	*temp;

	temp = q->head;
	while (temp && q->size)
	{
		if (temp->room_id == room_id)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	print_launch_room(int *launch_rooms, int num)
{
	int i;

	ft_printf("[launch rooms]\n");
	i = -1;
	while (++i < num)
		ft_printf("%d ", launch_rooms[i]);
	ft_printf("\n");
}

void	*ft_memdup(void *src, size_t n)
{
	void *ptr;

	ptr = (void*)ft_memalloc(n);
	ptr = ft_memcpy(ptr, src, n);
	return (ptr);
}

void	print_launch_room_dist(t_lem_in *lem_in)
{
	int i;

	i = 0;
	ft_printf("[launch room dist]\n");
	while (i < lem_in->num_launch_rooms)
	{
		ft_printf("%d ", lem_in->f_dist_to[lem_in->launch_rooms[i]]);
		i++;
	}
	ft_printf("\n");
}

int		set_solve_lim(int num_rooms, int num_ants)
{
	int lim;

	if (num_rooms < 2000)
		lim = 12;
	else
	{
		lim = 6;
		if (num_ants > 130)
			lim = 7;
		if (num_ants > 175)
			lim = 8;
		if (num_ants > 200)
			lim = 9;
		if (num_ants > 220)
			lim = 10;
		if (num_ants > 250)
			lim = 12;
		if (num_ants > 325)
			lim = 13;
		if (num_ants > 450)
			lim = 14;
	}
	return (lim);
}
