/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:46:47 by skunz             #+#    #+#             */
/*   Updated: 2019/03/08 15:38:02 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"

void			add_input_str(t_lem_in *lem_in, char *line)
{
	char *tmp;

	tmp = lem_in->input_str;
	lem_in->input_str = ft_strjoin_lb(lem_in->input_str, line);
	if (tmp)
		free(tmp);
}

static void		add_room(t_info *info, char *line)
{
	if (!info->rooms)
		info->rooms = ft_lstnew(line, ft_strlen(line) + 1);
	else
		ft_lstadd(&info->rooms, ft_lstnew(line, ft_strlen(line) + 1));
	info->room_count++;
}

static	void	add_command(t_lem_in *lem_in, t_info *info, char **line_ref)
{
	char *line;

	line = *line_ref;
	if (ft_strcmp(line, "##start") == 0)
		info->start_id == -1 ? info->start_id = info->room_count : ft_error();
	else if (ft_strcmp(line, "##end") == 0)
		info->end_id == -1 ? info->end_id = info->room_count : ft_error();
	else
		return ;
	add_input_str(lem_in, line);
	free(line);
	while (get_next_line(0, line_ref) > 0 && ft_strchr(*line_ref, '#'))
	{
		add_input_str(lem_in, *line_ref);
		free(*line_ref);
	}
	if (ft_strchr(*line_ref, ' '))
		add_room(info, *line_ref);
	else
		ft_error();
}

static	void	get_links(t_lem_in *lem_in, char *line, char *pos)
{
	char	*sub;
	int		idx;
	t_room	*ref;

	idx = -1;
	if ((pos = ft_strchr(line, '-')))
	{
		sub = ft_strsub(line, 0, pos - line);
		while (++idx < lem_in->num_rooms)
			if (ft_strcmp(lem_in->rooms[idx].name, sub) == 0)
			{
				!(ref = find_room(lem_in->rooms, lem_in->num_rooms, pos + 1))
					? ft_error() : 0;
				idx == ref->id ? ft_error() : 0;
				lem_in->a_graph[idx][ref->id] == 1 &&
					lem_in->a_graph[ref->id][idx] == 1 ? ft_error() : 0;
				lem_in->a_graph[idx][ref->id] = 1;
				lem_in->a_graph[ref->id][idx] = 1;
			}
		free(sub);
	}
	else if (!(line[0] == '#'))
		ft_error();
	add_input_str(lem_in, line);
	free(line);
}

void			get_data(t_lem_in *lem_in)
{
	char	*line;
	t_info	info;

	init_info(&info);
	info.ant_count = read_valid_number(lem_in);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strchr(line, ' ') && line[0] != '#')
			add_room(&info, line);
		else if (line[0] == '#' && line[1] == '#')
			add_command(lem_in, &info, &line);
		else if (ft_strchr(line, '-'))
			break ;
		else if (!(line[0] == '#'))
			ft_error();
		add_input_str(lem_in, line);
		free(line);
	}
	!line ? ft_error() : 0;
	translate_info(lem_in, &info);
	initialise_a_graph(lem_in);
	get_links(lem_in, line, NULL);
	while (get_next_line(0, &line) > 0)
		get_links(lem_in, line, NULL);
}
