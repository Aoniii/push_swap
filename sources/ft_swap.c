/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:59:53 by snourry           #+#    #+#             */
/*   Updated: 2022/05/01 20:59:53 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

static void	ft_operator(t_stack *stack)
{
	long long	tmp;
	long long	tmp1;

	stack = ft_firststack(stack);
	tmp = stack->integer;
	stack->integer = stack->next->integer;
	stack->next->integer = tmp;
	tmp1 = stack->index;
	stack->index = stack->next->index;
	stack->next->index = tmp1;
}

void	ft_swap(t_stack **stack, enum e_stack type)
{
	if (type == A)
	{
		ft_operator(stack[A]);
		ft_putendl_fd("sa", 1);
	}
	else if (type == B)
	{
		ft_operator(stack[B]);
		ft_putendl_fd("sb", 1);
	}
	else if (type == BOTH)
	{
		ft_operator(stack[A]);
		ft_operator(stack[B]);
		ft_putendl_fd("ss", 1);
	}
}
