/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:17:22 by snourry           #+#    #+#             */
/*   Updated: 2022/05/09 20:19:56 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

int	ft_get_min(t_stack **stack, enum e_stack type)
{
	t_stack	*a;
	int		min;

	a = stack[type];
	min = a->integer;
	while (a)
	{
		if (a->integer < min)
			min = a->integer;
		a = a->next;
	}
	return (min);
}

int	ft_get_max(t_stack **stack, enum e_stack type)
{
	t_stack	*a;
	int		max;

	a = stack[type];
	max = a->integer;
	while (a)
	{
		if (a->integer > max)
			max = a->integer;
		a = a->next;
	}
	return (max);
}
