/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:34:22 by snourry           #+#    #+#             */
/*   Updated: 2024/06/02 15:34:22 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static t_rotate	init_rotate(void)
{
	t_rotate	rotate;

	rotate.ra = 0;
	rotate.rb = 0;
	rotate.rra = 0;
	rotate.rrb = 0;
	return (rotate);
}

static int	count_rotate(t_rotate rotate)
{
	int	i;

	i = 0;
	while (rotate.ra > 0 && rotate.rb > 0)
	{
		rotate.ra--;
		rotate.rb--;
		i++;
	}
	while (rotate.rra > 0 && rotate.rrb > 0)
	{
		rotate.rra--;
		rotate.rrb--;
		i++;
	}
	return (i + rotate.ra + rotate.rb + rotate.rra + rotate.rrb);
}

static int	next(int x, t_stack *stack, int size)
{
	bool	found;
	int		i;
	int		next;
	int		tmp;

	found = 0;
	i = 0;
	next = 2147483647;
	while (i < size)
	{
		tmp = get_at_index(stack, i);
		if (tmp > x && tmp < next)
		{
			next = tmp;
			found = 1;
		}
		i++;
	}
	if (!found)
		next = get_min_value(stack);
	return (next);
}

static t_rotate	smart_calc(t_stack *stack, int next, t_rotate rotate, int size)
{
	int	i;

	i = 0;
	while (*((int *)(stack->content)) != next)
	{
		stack = stack->next;
		i++;
	}
	if (i <= size - i)
		rotate.ra = i;
	else
		rotate.rra = size - i;
	return (rotate);
}

t_rotate	calculate(t_container **container)
{
	t_rotate	rotate;
	t_rotate	rotate_tmp;
	int			i;
	int			size;

	i = 0;
	size = container[B]->size;
	while (i < size)
	{
		rotate_tmp = init_rotate();
		if (i <= size - i)
			rotate_tmp.rb = i;
		else
			rotate_tmp.rrb = size - i;
		rotate_tmp = smart_calc(container[A]->head, \
			next(get_at_index(container[B]->head, i), container[A]->head, \
			container[A]->size), rotate_tmp, container[A]->size);
		if (i == 0 || count_rotate(rotate) > count_rotate(rotate_tmp))
			rotate = rotate_tmp;
		if (count_rotate(rotate) <= 1)
			break ;
		i++;
	}
	return (rotate);
}
