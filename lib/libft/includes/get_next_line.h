/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:36:20 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/06 18:37:06 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 200
# define NULL_CHECK(call) if (!call) return (NULL)

typedef struct	s_thread
{
	int			fd;
	char		**cache;
}				t_thread;

int				get_next_line(const int fd, char **line);

#endif
