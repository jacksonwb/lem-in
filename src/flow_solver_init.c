/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_solver_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:15:29 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/08 15:33:58 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "flow_solver.h"

void	init_f(t_lem_in *lem_in)
{
	int	i;

	i = 0;
	while (i < lem_in->num_rooms)
	{
		lem_in->f_graph[lem_in->start_id][i] =
			lem_in->a_graph[lem_in->start_id][i];
		lem_in->f_graph[i][lem_in->start_id] =
			-lem_in->a_graph[lem_in->start_id][i];
		i++;
	}
}

void	init_r(t_lem_in *lem_in)
{
	int	i;
	int	j;

	i = 0;
	while (i < lem_in->num_rooms)
	{
		j = 0;
		while (j < lem_in->num_rooms)
		{
			if (i == j)
			{
				lem_in->r_graph[i + lem_in->num_rooms][j] = 1;
				lem_in->r_graph[i][j + lem_in->num_rooms] = 1;
			}
			lem_in->r_graph[i + lem_in->num_rooms][j] |= lem_in->a_graph[i][j];
			j++;
		}
		i++;
	}
}

void	init_q(t_lem_in *lem_in, t_queue *q)
{
	int i;

	i = 0;
	ft_bzero(q, sizeof(t_queue));
	while (i < lem_in->num_rooms)
	{
		if (lem_in->a_graph[lem_in->start_id][i] && i != lem_in->end_id)
			enqueue(q, i);
		i++;
	}
}

void	init_launch_rooms(t_lem_in *lem_in)
{
	int		i;
	int		count;
	t_bfs	*bfs;

	i = -1;
	count = 0;
	while (++i < lem_in->num_rooms)
	{
		if (lem_in->f_final_graph[lem_in->start_id][i] == 1)
			++count;
	}
	lem_in->launch_rooms = (int*)ft_memalloc(sizeof(int) * count);
	i = -1;
	count = 0;
	while (++i < lem_in->num_rooms)
	{
		if (lem_in->f_final_graph[lem_in->start_id][i] == 1)
			lem_in->launch_rooms[count++] = i;
	}
	lem_in->num_launch_rooms = count;
	bfs = bfs_from_t(lem_in, lem_in->f_final_graph);
	sort_launch_rooms(lem_in->launch_rooms, count, bfs->dist_to);
	lem_in->f_dist_to = ft_memdup(bfs->dist_to, sizeof(int) *
		lem_in->num_rooms);
	free_bfs(bfs);
}

void	init_flow_karp(t_lem_in *lem_in)
{
	lem_in->f_graph = graph_alloc(2 * lem_in->num_rooms);
	lem_in->r_graph = graph_alloc(2 * lem_in->num_rooms);
	set_room_distance(lem_in);
	if (lem_in->rooms[lem_in->start_id].distance == 0)
		ft_error();
	init_r(lem_in);
}
