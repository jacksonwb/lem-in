/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:27:11 by skunz             #+#    #+#             */
/*   Updated: 2019/03/08 15:28:34 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lem_in.h"

static	void	check_room_conflict(t_lem_in *lem_in, int idx, char **tab)
{
	int x;
	int y;

	x = ft_atoi(tab[1]);
	y = ft_atoi(tab[2]);
	while (idx < lem_in->num_rooms)
	{
		if (!ft_strcmp(lem_in->rooms[idx].name, tab[0]))
			ft_error();
		else if (lem_in->rooms[idx].x == x && lem_in->rooms[idx].y == y)
			ft_error();
		idx++;
	}
}

static	void	extract_room(t_lem_in *lem_in, char *line, int idx)
{
	int		i;
	char	**tab;
	int		len;

	i = 0;
	len = 0;
	lem_in->rooms[idx].id = idx;
	tab = ft_strsplit(line, ' ');
	while (tab[len])
		len++;
	if (len != 3)
		ft_error();
	lem_in->rooms[idx].name = tab[0];
	i = i + 1;
	if (!ft_is_integer(tab[1]))
		ft_error();
	lem_in->rooms[idx].x = ft_atoi(tab[1]);
	if (!ft_is_integer(tab[2]))
		ft_error();
	lem_in->rooms[idx].y = ft_atoi(tab[2]);
	check_room_conflict(lem_in, idx + 1, tab);
	free(tab[1]);
	free(tab[2]);
	free(tab);
}

t_room			*find_room(t_room *rooms, int size, char *name)
{
	int i;

	i = -1;
	while (++i < size)
	{
		if (ft_strcmp(rooms[i].name, name) == 0)
			return (&rooms[i]);
	}
	return (NULL);
}

void			translate_info(t_lem_in *farm, t_info *info)
{
	int		idx;
	t_list	*tmp;

	if (info == NULL)
		return ;
	idx = info->room_count;
	farm->num_rooms = info->room_count;
	if (!(farm->rooms = malloc(sizeof(t_room) * info->room_count)))
		ft_error();
	while (idx-- > 0)
	{
		extract_room(farm, info->rooms->content, idx);
		free(info->rooms->content);
		tmp = info->rooms->next;
		free(info->rooms);
		info->rooms = tmp;
	}
	if (info->start_id == -1 || info->end_id == -1 ||
		info->ant_count < 1 || info->start_id == info->end_id)
		ft_error();
	farm->start_id = info->start_id;
	farm->end_id = info->end_id;
	farm->num_ants = info->ant_count;
}
