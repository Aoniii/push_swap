/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 23:08:45 by snourry           #+#    #+#             */
/*   Updated: 2022/04/30 23:08:45 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

t_stack	*ft_newstack(t_stack *prev, t_stack *next, long long integer)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->prev = prev;
	stack->next = next;
	stack->integer = integer;
	stack->index = 0;
	return (stack);
}

t_stack	*ft_firststack(t_stack *stack)
{
	while (stack)
	{
		if (!stack->prev)
			return (stack);
		stack = stack->prev;
	}
	return (NULL);
}

t_stack	*ft_laststack(t_stack *stack)
{
	while (stack)
	{
		if (!stack->next)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

int	ft_sizestack(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i, stack)
		stack = stack->next;
	return (i);
}

void	ft_freestack(t_stack *stack)
{
	stack = ft_firststack(stack);
	while (stack->next)
	{
		stack = stack->next;
		free(stack->prev);
		stack->prev = NULL;
	}
	free(stack);
	stack = NULL;
}
