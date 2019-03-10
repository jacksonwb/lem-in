/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:37:16 by skunz             #+#    #+#             */
/*   Updated: 2019/03/08 15:29:43 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lem_in.h"

char	*ft_strjoin_lb(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		k;

	i = -1;
	k = -1;
	if (!s1 || !s2)
		return (NULL);
	if (!(join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2))))
		return (NULL);
	while (s1[++i])
		join[i] = s1[i];
	while (s2[++k])
		join[i + k] = s2[k];
	join[i + k] = '\n';
	join[i + k + 1] = '\0';
	return (join);
}

int		ft_is_integer(char *nbr_str)
{
	int		nb;
	char	*cmp_nbr_str;

	nb = ft_atoi(nbr_str);
	cmp_nbr_str = ft_itoa(nb);
	if (ft_strcmp(nbr_str, cmp_nbr_str) != 0)
		return (0);
	free(cmp_nbr_str);
	return (1);
}

int		read_valid_number(t_lem_in *lem_in)
{
	char	*line;
	int		nb;

	while (get_next_line(0, &line) > 0 && line[0] == '#' && line[1] != '#')
	{
		add_input_str(lem_in, line);
		free(line);
	}
	add_input_str(lem_in, line);
	if (ft_isdigit(line[0]))
	{
		if (!ft_is_integer(line))
			ft_error();
		nb = ft_atoi(line);
		free(line);
		return (nb);
	}
	else
		ft_error();
	return (0);
}

void	initialise_a_graph(t_lem_in *farm)
{
	int idx;

	idx = -1;
	if (!(farm->a_graph = malloc(sizeof(int*) * farm->num_rooms)))
		ft_error();
	while (++idx < farm->num_rooms)
	{
		if (!(farm->a_graph[idx] = malloc(sizeof(int) * farm->num_rooms)))
			ft_error();
		ft_bzero(farm->a_graph[idx], sizeof(int) * farm->num_rooms);
	}
}

void	init_info(t_info *info)
{
	info->ant_count = -1;
	info->room_count = 0;
	info->rooms = NULL;
	info->start_id = -1;
	info->end_id = -1;
}
