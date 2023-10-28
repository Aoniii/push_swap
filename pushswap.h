/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:07:39 by snourry           #+#    #+#             */
/*   Updated: 2022/05/09 20:25:12 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include "libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef struct s_stack
{
	struct s_stack	*prev;
	struct s_stack	*next;
	long long		integer;
	long long		index;
}					t_stack;

enum e_stack
{
	A,
	B,
	BOTH
};

/**
 * Stacks functions
 */

t_stack		*ft_newstack(t_stack *prev, t_stack *next, long long integer);
t_stack		*ft_firststack(t_stack *stack);
t_stack		*ft_laststack(t_stack *stack);
int			ft_sizestack(t_stack *stack);
void		ft_freestack(t_stack *stack);

/**
 * Sorts functions
 */

void		ft_swap(t_stack **stack, enum e_stack type);
void		ft_push(t_stack **stack, enum e_stack type);
void		ft_rotate(t_stack **stack, enum e_stack type);
void		ft_reverse_rotate(t_stack **stack, enum e_stack type);
void		ft_sort(t_stack **stack);
void		ft_sort_three(t_stack **stack);
void		ft_sort_big(t_stack **stack);

/**
 * Others functions
 */

t_stack		*ft_get_args(int argc, char **argv);
int			ft_error(t_stack **stack);
int			ft_check_maxint(t_stack *stack);
int			ft_check_mult(t_stack *stack);
int			ft_check_sort(t_stack *stack);
long long	ft_atoll(char *nptr);
int			ft_get_min(t_stack **stack, enum e_stack type);
int			ft_get_max(t_stack **stack, enum e_stack type);
void		ft_setindex(t_stack	**stack);

#endif