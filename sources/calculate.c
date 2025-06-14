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

/*
*	Initialize the rotate
*/
static t_rotate	init_rotate(void)
{
	t_rotate	rotate;

	rotate.ra = 0;
	rotate.rb = 0;
	rotate.rra = 0;
	rotate.rrb = 0;
	return (rotate);
}

/*
*	Count the number of rotate
*/
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

/*
*	Get the next value of the list
*/
static int	next(int x, t_list *list)
{
	bool	found;
	int		i;
	int		next;
	int		size;
	int		tmp;

	found = 0;
	i = 0;
	next = 2147483647;
	size = ft_lstsize(list);
	while (i < size)
	{
		tmp = get_at_index(list, i);
		if (tmp > x && tmp < next)
		{
			next = tmp;
			found = 1;
		}
		i++;
	}
	if (!found)
		next = get_min_value(list);
	return (next);
}

/*
*	Calculate the rotate to the list
*/
static t_rotate	smart_calc(t_list *list, int next, t_rotate rotate)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lstsize(list);
	while (*((int *)(list->content)) != next)
	{
		list = list->next;
		i++;
	}
	if (i <= size - i)
		rotate.ra = i;
	else
		rotate.rra = size - i;
	return (rotate);
}

/*
*	Calculate the rotate to the list
*	The code are slow because he try multiple rotate possibilities
*	Return the rotate
*/
t_rotate	calculate(t_list **list)
{
	t_rotate	rotate;
	t_rotate	rotate_tmp;
	int			i;
	int			size;
	int			n;

	i = 0;
	size = ft_lstsize(list[B]);
	while (i < size)
	{
		rotate_tmp = init_rotate();
		if (i <= size - i)
			rotate_tmp.rb = i;
		else
			rotate_tmp.rrb = size - i;
		n = next(get_at_index(list[B], i), list[A]);
		rotate_tmp = smart_calc(list[A], n, rotate_tmp);
		if (i == 0 || count_rotate(rotate) > count_rotate(rotate_tmp))
			rotate = rotate_tmp;
		if (count_rotate(rotate) <= 1)
			break ;
		i++;
	}
	return (rotate);
}
