/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_solver.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:57:53 by jbeall            #+#    #+#             */
/*   Updated: 2019/03/08 14:29:52 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOW_SOLVER_H
# define FLOW_SOLVER_H

typedef struct		s_elem
{
	int				room_id;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_queue
{
	t_elem			*head;
	t_elem			*last;
	int				size;
}					t_queue;

typedef struct		s_bfs
{
	t_queue			*q;
	int				**rev_graph;
	int				*marked;
	int				*edge_to;
	int				*dist_to;
	int				num_rooms;
}					t_bfs;

/*
** INIT
*/
void				init_flow(t_lem_in *lem_in, t_queue *q);
void				init_launch_rooms(t_lem_in *lem_in);
void				init_flow_karp(t_lem_in *lem_in);
void				init_f(t_lem_in *lem_in);
void				init_r(t_lem_in *lem_in);
void				init_q(t_lem_in *lem_in, t_queue *q);
void				push(t_lem_in *lem_in, int u, int v);

/*
** FLOW_SOLVER
*/
void				enqueue(t_queue *q, int room_id);
int					dequeue(t_queue *q);
void				set_room_distance(t_lem_in *lem_in);
int					queue_contains(t_queue *q, int room_id);
void				solve_flow_karp(t_lem_in *lem_in);
int					*has_augmenting_path(t_lem_in *lem_in, int
	**graph, int s, int t);
int					set_solve_lim(int num_rooms, int num_ants);
void				*ft_memdup(void *src, size_t n);
void				augment_flow(t_lem_in *lem_in, int u, int v);
void				sort_launch_rooms(int *launch_rooms, int len, int *dist_to);
int					is_start_or_end(t_lem_in *lem_in, int u, int v);

/*
** BFS
*/
void				gen_rev_graph(int **rev_graph, t_lem_in *lem_in,
	int **graph);
t_bfs				*bfs_from_t(t_lem_in *lem_in, int **graph);
t_bfs				*init_bfs(int num_rooms);
void				free_bfs(t_bfs *bfs);
void				free_queue(t_queue *q);
void				free_graph(int **graph, int n);
int					**graph_alloc(int n);
t_bfs				*run_bfs(int **graph, int s, int len);

/*
** COMPRESS
*/
int					**compress_f_graph(int **f_graph, int num_rooms);

/*
** PRINT
*/
void				print_graph(int **graph, int num_rooms);
void				print_info(t_lem_in *lem_in);
void				print_bfs(t_bfs *bfs);
void				print_launch_room(int *launch_rooms, int num);
void				print_launch_room_dist(t_lem_in *lem_in);
#endif
