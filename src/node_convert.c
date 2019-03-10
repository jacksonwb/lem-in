/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:58:38 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/08 12:25:26 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "flow_solver.h"

int		**compress_f_graph(int **f_graph, int num_rooms)
{
	int **f_final_graph;
	int i;
	int j;

	f_final_graph = graph_alloc(num_rooms);
	i = 0;
	while (i < num_rooms)
	{
		j = 0;
		while (j < num_rooms)
		{
			if (f_graph[i + num_rooms][j] == 1)
				f_final_graph[i][j] = 1;
			j++;
		}
		i++;
	}
	return (f_final_graph);
}

void	free_queue(t_queue *q)
{
	t_elem	*ptr;
	t_elem	*nxt;

	if (q->size)
	{
		ptr = q->head;
		while (ptr)
		{
			nxt = ptr->next;
			free(ptr);
			ptr = nxt;
		}
	}
	free(q);
}
