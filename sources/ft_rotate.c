/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:09:24 by snourry           #+#    #+#             */
/*   Updated: 2022/05/04 14:42:11 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

static void	ft_operator(t_stack **stack, enum e_stack type)
{
	t_stack	*start;
	t_stack	*last;
	t_stack	*tmp;

	start = ft_firststack(stack[type]);
	if (!start->next)
		return ;
	last = ft_laststack(stack[type]);
	tmp = start;
	start = start->next;
	start->prev = NULL;
	tmp->next = NULL;
	tmp->prev = last;
	last->next = tmp;
	stack[type] = start;
}

void	ft_rotate(t_stack **stack, enum e_stack type)
{
	if (type == A)
	{
		ft_operator(stack, A);
		ft_putendl_fd("ra", 1);
	}
	else if (type == B)
	{
		ft_operator(stack, B);
		ft_putendl_fd("rb", 1);
	}
	else if (type == BOTH)
	{
		ft_operator(stack, A);
		ft_operator(stack, B);
		ft_putendl_fd("rr", 1);
	}
}
