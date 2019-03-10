/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:47:28 by skunz             #+#    #+#             */
/*   Updated: 2019/03/08 15:32:51 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define Q_FLAG 1
# define L_FLAG 2
# define D_FLAG 4

typedef	struct	s_info
{
	int			ant_count;
	int			room_count;
	t_list		*rooms;
	int			start_id;
	int			end_id;
}				t_info;

typedef struct	s_room
{
	char		*name;
	int			id;
	int			x;
	int			y;
	int			distance;
}				t_room;

typedef struct	s_lem_in
{
	t_room		*rooms;
	char		flag;
	int			num_ants;
	int			num_rooms;
	int			*launch_rooms;
	int			*f_dist_to;
	int			num_launch_rooms;
	int			**a_graph;
	int			**f_graph;
	int			**r_graph;
	int			**f_final_graph;
	int			*e;
	int			*h;
	int			start_id;
	int			end_id;
	int			min_dist;
	char		*input_str;
}				t_lem_in;

void			ant_runner(t_lem_in *lem_in);
void			ft_error(void);
#endif
