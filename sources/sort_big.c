/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:46:57 by snourry           #+#    #+#             */
/*   Updated: 2024/05/30 22:46:57 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	push_median(t_container **container, int median)
{
	t_stack	*stack;
	int		i;

	i = 0;
	stack = container[A]->head;
	while (*((int *)(stack->content)) != median)
	{
		stack = stack->next;
		i++;
	}
	if (i <= container[A]->size - i)
		while (i--)
			rotate(container, A, 1);
	else
	{
		i = container[A]->size - i;
		while (i--)
			reverse_rotate(container, A, 1);
	}
	push(container, B, 1);
}

static void	push_b(t_container **container, int median)
{
	int	max;
	int	size;

	max = identify_top(container[A]->head, 5);
	size = container[A]->size;
	while (size > 5)
	{
		if (*((int *)(container[A]->head->content)) < max)
		{
			push(container, B, 1);
			size--;
			if (*((int *)(container[B]->head->content)) > median)
			{
				if (*((int *)(container[A]->head->content)) >= max && \
				container[A]->head->next)
					rotate(container, BOTH, 1);
				else
					rotate(container, B, 1);
			}
		}
		else
			rotate(container, A, 1);
	}
}

static void	apply(t_container **container, t_rotate r)
{
	while (r.ra > 0 && r.rb > 0)
	{
		r.ra--;
		r.rb--;
		rotate(container, BOTH, 1);
	}
	while (r.rra > 0 && r.rrb > 0)
	{
		r.rra--;
		r.rrb--;
		reverse_rotate(container, BOTH, 1);
	}
	while (r.ra--)
		rotate(container, A, 1);
	while (r.rb--)
		rotate(container, B, 1);
	while (r.rra--)
		reverse_rotate(container, A, 1);
	while (r.rrb--)
		reverse_rotate(container, B, 1);
	push(container, A, 1);
}

static void	set_first(t_container **container)
{
	t_stack	*tmp;
	int		i;
	int		min;
	int		size;

	tmp = container[A]->head;
	i = 0;
	min = get_min_value(tmp);
	size = container[A]->size;
	while (*((int *)(tmp->content)) != min)
	{
		tmp = tmp->next;
		i++;
	}
	if (i <= size - i)
	{
		while (i--)
			rotate(container, A, 1);
		return ;
	}
	i = size - i;
	while (i--)
		reverse_rotate(container, A, 1);
}

void	sort_big(t_container **container)
{
	t_rotate	rotate;
	int			median;

	median = get_median(container);
	push_median(container, median);
	push_b(container, median);
	sort_five(container);
	while (container[B]->head)
	{
		rotate = calculate(container);
		apply(container, rotate);
	}
	set_first(container);
}
