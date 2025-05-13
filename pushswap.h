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
}	t_rotate;

typedef struct s_stack
{
	void			*content;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

typedef struct s_container
{
	t_stack	*head;
	t_stack	*tail;
	int		size;
}			t_container;

t_container	*args(char **argv);
t_container	*creat(char **argv);
void		swap(t_container **container, t_type type, bool print);
void		push(t_container **container, t_type type, bool print);
void		rotate(t_container **container, t_type type, bool print);
void		reverse_rotate(t_container **container, t_type type, bool print);
void		sort(t_container **container);
void		sort_five(t_container **container);
void		sort_big(t_container **container);
void		free_argv(char **argv);
bool		is_sorted(t_container **container);
int			get_max_value(t_stack *stack);
int			get_min_value(t_stack *stack);
int			get_at_index(t_stack *stack, int index);
int			find_min(t_stack *stack, int min);
int			find_max(t_stack *stack, int max);
int			identify_bottom(t_stack *stack, int bottom);
int			identify_top(t_stack *stack, int top);
int			get_median(t_container **container);
t_rotate	calculate(t_container **container);
void		stack_clear(t_stack **lst, void (*del) (void*));
void		stack_delone(t_stack *lst, void (*del) (void*));
t_stack		*stack_new(void *content);

#endif
