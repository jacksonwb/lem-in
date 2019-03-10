/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_solver_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:11:28 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/04 19:22:16 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "flow_solver.h"

int		**graph_alloc(int n)
{
	int	i;
	int	**graph;

	i = 0;
	graph = (int**)ft_memalloc(sizeof(int*) * n);
	while (i < n)
	{
		graph[i] = (int*)ft_memalloc(sizeof(int) * n);
		i++;
	}
	return (graph);
}

void	free_graph(int **graph, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(graph[i]);
		i++;
	}
	free(graph);
}

void	set_room_distance(t_lem_in *lem_in)
{
	t_bfs	*bfs;
	int		i;

	bfs = bfs_from_t(lem_in, lem_in->a_graph);
	i = 0;
	while (i < lem_in->num_rooms)
	{
		lem_in->rooms[i].distance = bfs->dist_to[i];
		i++;
	}
	free_bfs(bfs);
}

void	enqueue(t_queue *q, int room_id)
{
	t_elem	*new;

	new = (t_elem*)ft_memalloc(sizeof(t_elem));
	new->room_id = room_id;
	if (q->size)
		q->last->next = new;
	else
		q->head = new;
	q->last = new;
	q->size += 1;
}

int		dequeue(t_queue *q)
{
	int		room_id;
	t_elem	*temp;

	if (q->size)
	{
		room_id = q->head->room_id;
		temp = q->head;
		q->head = q->head->next;
		free(temp);
		if (q->size == 1)
			q->last = q->last->next;
		q->size -= 1;
	}
	else
		room_id = -1;
	return (room_id);
}
