/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 23:35:38 by snourry           #+#    #+#             */
/*   Updated: 2022/04/30 23:35:38 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

int	ft_error(t_stack **stack)
{
	if (stack[A])
		ft_freestack(stack[A]);
	free(stack);
	stack = NULL;
	ft_putendl_fd("Error", 1);
	return (0);
}

int	ft_check_maxint(t_stack *stack)
{
	stack = ft_firststack(stack);
	while (stack)
	{
		if (stack->integer > 2147483647 || stack->integer < -2147483648)
			return (FALSE);
		stack = stack->next;
	}
	return (TRUE);
}

int	ft_check_mult(t_stack *stack)
{
	t_stack	*s1;
	t_stack	*s2;

	s1 = ft_firststack(stack);
	while (s1)
	{
		s2 = s1->next;
		while (s2)
		{
			if (s1->integer == s2->integer)
				return (FALSE);
			s2 = s2->next;
		}
		s1 = s1->next;
	}
	return (TRUE);
}

int	ft_check_sort(t_stack *stack)
{
	stack = ft_firststack(stack);
	stack = stack->next;
	while (stack)
	{
		if (stack->integer < stack->prev->integer)
			return (FALSE);
		stack = stack->next;
	}
	return (TRUE);
}
