/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:27:24 by snourry           #+#    #+#             */
/*   Updated: 2024/05/26 21:27:24 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

typedef enum e_type
{
	A,
	B,
	BOTH
}	t_type;

typedef struct s_rotate
{
	int	ra;
	int	rra;
	int	rb;
	int	rrb;
}		t_rotate;

t_list		*args(char **argv);
void		swap(t_list **list, t_type type, bool print);
void		push(t_list **list, t_type type, bool print);
void		rotate(t_list **list, t_type type, bool print);
void		reverse_rotate(t_list **list, t_type type, bool print);
void		sort(t_list **list);
void		sort_five(t_list **list);
void		sort_big(t_list **list);
void		free_argv(char **argv);
bool		is_sorted(t_list **list);
int			get_max_value(t_list *list);
int			get_min_value(t_list *list);
int			get_at_index(t_list *list, int index);
int			find_min(t_list *list, int min);
int			find_max(t_list *list, int max);
int			identify_bottom(t_list *list, int bottom);
int			identify_top(t_list *list, int top);
int			get_median(t_list **list);
t_rotate	calculate(t_list **list);

#endif
