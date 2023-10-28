/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:09:24 by snourry           #+#    #+#             */
/*   Updated: 2022/05/04 14:42:01 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

static void	ft_operator(t_stack **stack, enum e_stack type)
{
	t_stack	*start;
	t_stack	*last;
	t_stack	*tmp;

	last = ft_laststack(stack[type]);
	if (!last->prev)
		return ;
	start = ft_firststack(stack[type]);
	tmp = last;
	last = last->prev;
	last->next = NULL;
	tmp->prev = NULL;
	tmp->next = start;
	start->prev = tmp;
	stack[type] = tmp;
}

void	ft_reverse_rotate(t_stack **stack, enum e_stack type)
{
	if (type == A)
	{
		ft_operator(stack, A);
		ft_putendl_fd("rra", 1);
	}
	else if (type == B)
	{
		ft_operator(stack, B);
		ft_putendl_fd("rrb", 1);
	}
	else if (type == BOTH)
	{
		ft_operator(stack, A);
		ft_operator(stack, B);
		ft_putendl_fd("rrr", 1);
	}
}
