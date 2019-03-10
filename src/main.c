/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 13:14:18 by skunz             #+#    #+#             */
/*   Updated: 2019/03/08 15:53:09 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"
#include "flow_solver.h"

void	ft_error(void)
{
	ft_putstr("ERROR\n");
	exit(-1);
}

int		is_flag(char c)
{
	return (c == 'q');
}

void	ft_usage(void)
{
	ft_printf("Usage: lem-in [-q | -l] < map\n");
	exit(0);
}

int		main(int argc, char **argv)
{
	t_lem_in	lem_in;
	int			i;

	i = 0;
	ft_bzero(&lem_in, sizeof(t_lem_in));
	if (argc > 1)
	{
		while (++i < argc)
		{
			if (ft_strcmp(argv[i], "-q") == 0)
				lem_in.flag |= Q_FLAG;
			else if (ft_strcmp(argv[i], "-l") == 0)
				lem_in.flag |= L_FLAG;
			else if (ft_strcmp(argv[i], "-d") == 0)
				lem_in.flag |= D_FLAG;
			else
				ft_usage();
		}
	}
	lem_in.input_str = ft_strdup("");
	get_data(&lem_in);
	solve_flow_karp(&lem_in);
	lem_in.flag & D_FLAG ? print_info(&lem_in) : 0;
	ant_runner(&lem_in);
	return (0);
}
