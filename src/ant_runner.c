/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:49:28 by skunz             #+#    #+#             */
/*   Updated: 2019/03/08 15:56:06 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ant_stack.h"
#include <limits.h>

/*
** A turn is defined as
** 	-move cycle, ants are beging moved to the next room
**	-send cycle, ants are send out from the start
*/

void	remove_ant(t_ant_stack *ants, t_ant_list **head_ref,
	t_ant_list **prev_ref)
{
	t_ant_list *tmp;
	t_ant_list *head;
	t_ant_list *prev;

	head = *head_ref;
	prev = *prev_ref;
	if (head == ants->top)
	{
		ants->top = ants->top->next;
		free(head);
	}
	else
	{
		tmp = head->next;
		free(head);
		head = prev;
		prev->next = tmp;
	}
	ants->size--;
	*head_ref = head;
	*prev_ref = prev;
}

void	move_ants(t_ant_stack *ants, t_lem_in *lem_in)
{
	t_ant_list	*head;
	t_ant_list	*prev;
	int			i;

	head = ants->top;
	prev = NULL;
	while (head)
	{
		i = -1;
		while (++i < lem_in->num_rooms)
		{
			if (lem_in->f_final_graph[head->room_id][i] == 1)
			{
				head->room_id = i;
				ft_printf("L%d-%s", head->ant_num, lem_in->rooms[i].name);
				if (head->next)
					ft_printf(" ");
				if (lem_in->end_id == head->room_id)
					remove_ant(ants, &head, &prev);
				break ;
			}
		}
		prev = head;
		head = head->next;
	}
}

void	send_ants(t_ant_stack *ants, t_lem_in *lem_in, int *current)
{
	int i;
	int d1;
	int d2;
	int id2;
	int ant_sum;

	i = -1;
	ant_sum = 0;
	d1 = lem_in->f_dist_to[lem_in->launch_rooms[0]];
	while (++i < lem_in->num_launch_rooms && *current != lem_in->num_ants + 1)
	{
		id2 = lem_in->launch_rooms[i];
		d2 = lem_in->f_dist_to[id2];
		ant_sum += i * (d2 - d1);
		if (lem_in->num_ants - *current + 1 > ant_sum)
		{
			lem_in->end_id != id2 ? push_ant(ants, id2, *current) : 0;
			*current != 1 && ants->size ? ft_printf(" ") : 0;
			ft_printf("L%d-%s", *current, lem_in->rooms[id2].name);
			*current += 1;
		}
		else
			break ;
		d1 = d2;
	}
}

void	ant_runner(t_lem_in *lem_in)
{
	t_ant_stack	ants;
	int			current;
	int			line_count;

	ants.top = NULL;
	ants.size = 0;
	line_count = 0;
	current = 1;
	if ((lem_in->flag & Q_FLAG) == 0)
	{
		write(1, lem_in->input_str, ft_strlen(lem_in->input_str));
		ft_printf("\n");
	}
	while (current < lem_in->num_ants + 1 || ants.size)
	{
		move_ants(&ants, lem_in);
		send_ants(&ants, lem_in, &current);
		ft_printf("\n");
		line_count++;
	}
	if (lem_in->flag & L_FLAG)
		ft_printf("Number of Turns: %d\n", line_count);
}
