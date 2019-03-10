/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:05:53 by skunz             #+#    #+#             */
/*   Updated: 2019/03/08 15:32:55 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"

typedef struct s_lem_in	t_lem_in;
typedef struct s_room	t_room;
typedef struct s_info	t_info;

/*
** parser.c
*/

void	get_data(t_lem_in *lem_in);
void	add_input_str(t_lem_in *lem_in, char *line);

/*
** translate.c
*/

void	translate_info(t_lem_in *farm, t_info *info);
t_room	*find_room(t_room *rooms, int size, char *name);

/*
** parser_helper.c
*/

void	init_info(t_info *info);
char	*ft_strjoin_lb(char const *s1, char const *s2);
int		read_valid_number(t_lem_in *lem_in);
void	initialise_a_graph(t_lem_in *lem_in);
int		ft_is_integer(char *nbr_str);

#endif
