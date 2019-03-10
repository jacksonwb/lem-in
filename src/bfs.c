/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:12:15 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/08 12:13:36 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "flow_solver.h"

void	gen_rev_graph(int **rev_graph, t_lem_in *lem_in, int **graph)
{
	int	i;
	int	j;

	i = 0;
	while (i < lem_in->num_rooms)
	{
		j = 0;
		while (j < lem_in->num_rooms)
		{
			if (graph[i][j] == 1)
				rev_graph[j][i] = 1;
			j++;
		}
		i++;
	}
}

t_bfs	*init_bfs(int num_rooms)
{
	t_bfs	*bfs;

	bfs = (t_bfs*)ft_memalloc(sizeof(t_bfs));
	bfs->q = (t_queue*)ft_memalloc(sizeof(t_queue));
	bfs->rev_graph = graph_alloc(num_rooms);
	bfs->marked = (int*)ft_memalloc(sizeof(int) * num_rooms);
	bfs->edge_to = (int*)ft_memalloc(sizeof(int) * num_rooms);
	bfs->dist_to = (int*)ft_memalloc(sizeof(int) * num_rooms);
	bfs->num_rooms = num_rooms;
	return (bfs);
}

t_bfs	*bfs_from_t(t_lem_in *lem_in, int **graph)
{
	t_bfs	*bfs;
	int		v;
	int		w;

	bfs = init_bfs(lem_in->num_rooms);
	gen_rev_graph(bfs->rev_graph, lem_in, graph);
	enqueue(bfs->q, lem_in->end_id);
	bfs->marked[lem_in->end_id] = 1;
	while (bfs->q->size)
	{
		v = dequeue(bfs->q);
		w = 0;
		while (w < lem_in->num_rooms)
		{
			if (bfs->rev_graph[v][w])
				if (!bfs->marked[w] && (bfs->marked[w] = 1))
				{
					enqueue(bfs->q, w);
					bfs->edge_to[w] = v;
					bfs->dist_to[w] = bfs->dist_to[v] + 1;
				}
			w++;
		}
	}
	return (bfs);
}

t_bfs	*run_bfs(int **graph, int s, int len)
{
	t_bfs	*bfs;
	int		v;
	int		w;
	int		offset;

	bfs = init_bfs(len);
	enqueue(bfs->q, s);
	bfs->marked[s] = 1;
	while (bfs->q->size)
	{
		v = dequeue(bfs->q);
		offset = v < len / 2 ? len / 2 : 0;
		w = -1;
		while (++w + offset < len / 2 + offset)
		{
			if (graph[v][w + offset])
				if (!bfs->marked[w + offset] && (bfs->marked[w + offset] = 1))
				{
					enqueue(bfs->q, w + offset);
					bfs->edge_to[w + offset] = v;
					bfs->dist_to[w + offset] = bfs->dist_to[v] + 1;
				}
		}
	}
	return (bfs);
}

void	free_bfs(t_bfs *bfs)
{
	free(bfs->dist_to);
	free(bfs->edge_to);
	free(bfs->marked);
	free_queue(bfs->q);
	free_graph(bfs->rev_graph, bfs->num_rooms);
	free(bfs);
}
