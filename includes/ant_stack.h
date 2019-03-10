/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_stack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:51:20 by skunz             #+#    #+#             */
/*   Updated: 2019/03/03 11:26:11 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANT_STACK_H
# define ANT_STACK_H

# include <stdlib.h>

typedef	struct	s_ant_list
{
	int					room_id;
	int					ant_num;
	struct s_ant_list	*next;
}				t_ant_list;

typedef	struct	s_ant_stack
{
	t_ant_list	*top;
	int			size;
}				t_ant_stack;

void			push_ant(t_ant_stack *ants, int room_id, int ant_num);

#endif
