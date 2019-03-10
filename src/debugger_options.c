/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:48:36 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/08 13:15:46 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "flow_solver.h"
#include "ant_stack.h"

void	print_graph(int **graph, int num_rooms)
{
	int i;
	int j;

	i = 0;
	while (i < num_rooms)
	{
		j = 0;
		while (j < num_rooms)
		{
			ft_printf("%d ", graph[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_info(t_lem_in *lem_in)
{
	ft_printf("\n==Lem-in-Info==\n");
	ft_printf("Ant Count  [%d]\n", lem_in->num_ants);
	ft_printf("Room Count [%d]\n", lem_in->num_rooms);
	ft_printf("Start ID   [%d]\n", lem_in->start_id);
	ft_printf("End ID     [%d]\n\n", lem_in->end_id);
	print_launch_room(lem_in->launch_rooms, lem_in->num_launch_rooms);
	print_launch_room_dist(lem_in);
	ft_printf("\n-A Graph-\n");
	print_graph(lem_in->a_graph, lem_in->num_rooms);
	ft_printf("\n-R Graph-\n");
	print_graph(lem_in->r_graph, 2 * lem_in->num_rooms);
	ft_printf("\n-F Graph-\n");
	print_graph(lem_in->f_graph, 2 * lem_in->num_rooms);
	ft_printf("\n-F Final Graph-\n");
	print_graph(lem_in->f_final_graph, lem_in->num_rooms);
}

void	print_bfs(t_bfs *bfs)
{
	int i;

	i = 0;
	ft_printf("marked[]\n");
	while (i < bfs->num_rooms)
		ft_printf("%d ", bfs->marked[i++]);
	ft_printf("\n");
	i = 0;
	ft_printf("edge_to[]\n");
	while (i < bfs->num_rooms)
		ft_printf("%d ", bfs->edge_to[i++]);
	ft_printf("\n");
	i = 0;
	ft_printf("dist_to[]\n");
	while (i < bfs->num_rooms)
		ft_printf("%d ", bfs->dist_to[i++]);
	ft_printf("\n");
	ft_printf("rev_graph:\n");
	print_graph(bfs->rev_graph, bfs->num_rooms);
}

void	print_stack(t_ant_stack ants)
{
	ft_printf("===Ant Stack===\n");
	while (ants.top)
	{
		ft_printf("room_id %d\n", ants.top->room_id);
		ft_printf("ant_num %d\n", ants.top->ant_num);
		ft_printf("-----\n");
		ants.top = ants.top->next;
	}
}
