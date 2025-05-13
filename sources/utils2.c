/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:00:36 by snourry           #+#    #+#             */
/*   Updated: 2024/06/01 12:00:36 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	find_min(t_stack *stack, int min)
{
	int	out;

	out = 2147483647;
	while (stack)
	{
		if (*((int *)(stack->content)) < out && \
		*((int *)(stack->content)) > min)
			out = *((int *)(stack->content));
		stack = stack->next;
	}
	return (out);
}

int	find_max(t_stack *stack, int max)
{
	int	out;

	out = -2147483648;
	while (stack)
	{
		if (*((int *)(stack->content)) > out && \
		*((int *)(stack->content)) < max)
			out = *((int *)(stack->content));
		stack = stack->next;
	}
	return (out);
}

int	identify_bottom(t_stack *stack, int bottom)
{
	int	prev;
	int	i;

	prev = get_min_value(stack);
	i = 1;
	while (i < bottom)
	{
		prev = find_min(stack, prev);
		i++;
	}
	return (prev);
}

int	identify_top(t_stack *stack, int top)
{
	int	prev;
	int	i;

	prev = get_max_value(stack);
	i = 1;
	while (i < top)
	{
		prev = find_max(stack, prev);
		i++;
	}
	return (prev);
}

int	get_median(t_container **container)
{
	int	prev;
	int	size;
	int	i;

	size = container[A]->size;
	prev = get_min_value(container[A]->head);
	i = 1;
	while (i < size / 2)
	{
		prev = find_min(container[A]->head, prev);
		i++;
	}
	return (prev);
}
