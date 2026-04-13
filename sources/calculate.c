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
*	Get the next value of the list
*/
static int	next(int x, t_list *list)
{
	bool	found;
	int		n;
	int		tmp;
	t_list	*cur;

	found = 0;
	n = 2147483647;
	cur = list;
	while (cur)
	{
		tmp = *((int *)(cur->content));
		if (tmp > x && tmp < n)
		{
			n = tmp;
			found = 1;
		}
		cur = cur->next;
	}
	if (!found)
		n = get_min_value(list);
	return (n);
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

static t_rotate	calc_cost(t_list **list, t_list *cur, int i, int size)
{
	t_rotate	tmp;
	int			n;

	tmp = init_rotate();
	if (i <= size - i)
		tmp.rb = i;
	else
		tmp.rrb = size - i;
	n = next(*((int *)(cur->content)), list[A]);
	tmp = smart_calc(list[A], n, tmp);
	return (tmp);
}

/*
*	Calculate the rotate to the list
*	Return the rotate
*/
t_rotate	calculate(t_list **list)
{
	t_rotate	rotate;
	t_rotate	tmp;
	int			i;
	t_list		*cur;

	i = 0;
	cur = list[B];
	while (cur)
	{
		tmp = calc_cost(list, cur, i, ft_lstsize(list[B]));
		if (i == 0 || count_rotate(rotate) > count_rotate(tmp))
			rotate = tmp;
		if (count_rotate(rotate) <= 1)
			break ;
		cur = cur->next;
		i++;
	}
	return (rotate);
}
