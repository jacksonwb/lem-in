/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:57:55 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/08 15:54:43 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "flow_solver.h"

void	sort_launch_rooms(int *launch_rooms, int len, int *dist_to)
{
	int sorted;
	int i;
	int temp;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < len - 1)
		{
			if (dist_to[launch_rooms[i]] > dist_to[launch_rooms[i + 1]])
			{
				temp = launch_rooms[i];
				launch_rooms[i] = launch_rooms[i + 1];
				launch_rooms[i + 1] = temp;
				sorted = 0;
			}
			++i;
		}
	}
}

int		*has_augmenting_path(t_lem_in *lem_in, int **graph, int s, int t)
{
	t_bfs	*bfs;
	int		*path;

	bfs = run_bfs(graph, s, 2 * lem_in->num_rooms);
	if (bfs->marked[t])
		path = ft_memdup(bfs->edge_to, sizeof(int) * 2 * lem_in->num_rooms);
	else
		path = NULL;
	free_bfs(bfs);
	return (path);
}

void	augment_flow(t_lem_in *lem_in, int u, int v)
{
	lem_in->r_graph[u][v] -= 1;
	lem_in->r_graph[v][u] += 1;
	lem_in->f_graph[u][v] += 1;
	lem_in->f_graph[v][u] -= 1;
}

int		is_start_or_end(t_lem_in *lem_in, int u, int v)
{
	if (u == lem_in->start_id || v == lem_in->end_id + lem_in->num_rooms)
		return (1);
	else
		return (0);
}

void	solve_flow_karp(t_lem_in *lem_in)
{
	int *path;
	int u;
	int v;
	int i;
	int lim;

	u = -1;
	i = 0;
	lim = set_solve_lim(lem_in->num_rooms, lem_in->num_ants);
	init_flow_karp(lem_in);
	while ((path = has_augmenting_path(lem_in, lem_in->r_graph,
		lem_in->start_id, lem_in->end_id + lem_in->num_rooms)) && i++ <= lim)
	{
		v = lem_in->end_id + lem_in->num_rooms;
		while (v != lem_in->start_id)
		{
			u = path[v];
			!is_start_or_end(lem_in, u, v) ? augment_flow(lem_in, u, v) : 0;
			v = u;
		}
		free(path);
	}
	lem_in->f_final_graph = compress_f_graph(lem_in->f_graph,
		lem_in->num_rooms);
	init_launch_rooms(lem_in);
}
