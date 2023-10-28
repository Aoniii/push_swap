/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:39:57 by snourry           #+#    #+#             */
/*   Updated: 2022/05/06 15:13:22 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

static long long	ft_get_mini(t_stack **stack)
{
	t_stack		*a;
	long long	min;

	a = stack[A];
	min = 2147483648;
	while (a)
	{
		if (a->integer < min && a->index == 0)
			min = a->integer;
		a = a->next;
	}
	return (min);
}

void	ft_setindex(t_stack	**stack)
{
	long long	l;
	long long	index;
	t_stack		*a;

	l = ft_get_mini(stack);
	index = 1;
	while (l != 2147483648)
	{
		a = ft_firststack(stack[A]);
		while (a)
		{
			if (a->integer == l)
			{
				a->index = index;
				break ;
			}
			a = a->next;
		}
		l = ft_get_mini(stack);
		index++;
	}
}
