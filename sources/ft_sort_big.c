/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_big.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:08:29 by snourry           #+#    #+#             */
/*   Updated: 2022/05/10 11:17:36 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

static void	ft_push_init(t_stack **stack, int size)
{
	int	i;

	i = 4;
	while (i)
	{
		while (ft_sizestack(stack[A]) > size / 5 * i + 4)
		{
			if (ft_firststack(stack[A])->index < size / 5 * (5 - i) + 1)
				ft_push(stack, B);
			else
				ft_rotate(stack, A);
		}
		i--;
	}
	while (ft_sizestack(stack[A]) > 3)
	{
		if (ft_firststack(stack[A])->index != size)
			ft_push(stack, B);
		else
			ft_rotate(stack, A);
	}
}

static void	ft_push_init_ultimate(t_stack **stack, int size)
{
	int	i;

	i = 19;
	while (i)
	{
		while (ft_sizestack(stack[A]) > size / 20 * i + 19)
		{
			if (ft_firststack(stack[A])->index < size / 20 * (20 - i) + 1)
				ft_push(stack, B);
			else
				ft_rotate(stack, A);
		}
		i--;
	}
	while (ft_sizestack(stack[A]) > 3)
	{
		if (ft_firststack(stack[A])->index != size)
			ft_push(stack, B);
		else
			ft_rotate(stack, A);
	}
}

static void	ft_repush(t_stack **stack, int size)
{
	while (stack[B])
	{
		stack[B] = ft_firststack(stack[B]);
		if (stack[B]->index < ft_firststack(stack[A])->index
			&& (stack[B]->index > ft_laststack(stack[A])->index
				|| ft_laststack(stack[A])->index == size))
			ft_push(stack, A);
		else
		{
			if (stack[B]->index < ft_firststack(stack[A])->index)
				ft_reverse_rotate(stack, A);
			else
				ft_rotate(stack, A);
		}
	}
	while (ft_firststack(stack[A])->index != 1)
		ft_reverse_rotate(stack, A);
}

void	ft_sort_big(t_stack **stack)
{
	int	size;

	ft_setindex(stack);
	size = ft_sizestack(stack[A]);
	if (size <= 100)
		ft_push_init(stack, size);
	else
		ft_push_init_ultimate(stack, size);
	ft_sort_three(stack);
	ft_repush(stack, size);
}
