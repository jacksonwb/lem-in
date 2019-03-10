/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:50:57 by skunz             #+#    #+#             */
/*   Updated: 2019/03/03 11:25:53 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ant_stack.h"

void	push_ant(t_ant_stack *ants, int room_id, int ant_num)
{
	t_ant_list *new;

	new = malloc(sizeof(t_ant_list));
	new->ant_num = ant_num;
	new->room_id = room_id;
	new->next = NULL;
	if (ants->top == NULL)
		ants->top = new;
	else
	{
		new->next = ants->top;
		ants->top = new;
	}
	ants->size++;
}
