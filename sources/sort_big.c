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

static void	push_median(t_list **list, int median)
{
	t_list	*lst;
	int		i;

	i = -1;
	lst = list[A];
	while (*((int *)(lst->content)) != median && ++i > 0)
		lst = lst->next;
	if (i <= ft_lstsize(list[A]) - i)
	{
		while (i--)
		{
			if (*((int *)(list[A]->content)) > median)
				push(list, B, 1);
			else
				rotate(list, A, 1);
		}
	}
	else
	{
		i = ft_lstsize(list[A]) - i;
		while (i--)
			reverse_rotate(list, A, 1);
	}
	push(list, B, 1);
}

static void	push_b(t_list **list, int median)
{
	int	max;
	int	size;

	max = identify_top(list[A], 5);
	size = ft_lstsize(list[A]);
	while (size > 5)
	{
		if (*((int *)(list[A]->content)) < max)
		{
			push(list, B, 1);
			size--;
			if (*((int *)(list[B]->content)) > median)
			{
				if (*((int *)(list[A]->content)) >= max && list[A]->next)
					rotate(list, BOTH, 1);
				else
					rotate(list, B, 1);
			}
		}
		else
			rotate(list, A, 1);
	}
}

static void	apply(t_list **list, t_rotate r)
{
	while (r.ra > 0 && r.rb > 0)
	{
		r.ra--;
		r.rb--;
		rotate(list, BOTH, 1);
	}
	while (r.rra > 0 && r.rrb > 0)
	{
		r.rra--;
		r.rrb--;
		reverse_rotate(list, BOTH, 1);
	}
	while (r.ra--)
		rotate(list, A, 1);
	while (r.rb--)
		rotate(list, B, 1);
	while (r.rra--)
		reverse_rotate(list, A, 1);
	while (r.rrb--)
		reverse_rotate(list, B, 1);
	push(list, A, 1);
}

static void	set_first(t_list **list)
{
	t_list	*tmp;
	int		i;
	int		min;
	int		size;

	tmp = list[A];
	i = 0;
	min = get_min_value(tmp);
	size = ft_lstsize(tmp);
	while (*((int *)(tmp->content)) != min)
	{
		tmp = tmp->next;
		i++;
	}
	if (i <= size - i)
	{
		while (i--)
			rotate(list, A, 1);
		return ;
	}
	i = size - i;
	while (i--)
		reverse_rotate(list, A, 1);
}

void	sort_big(t_list **list)
{
	t_rotate	rotate;
	int			median;

	median = get_median(list);
	push_median(list, median);
	push_b(list, median);
	sort_five(list);
	while (list[B])
	{
		rotate = calculate(list);
		apply(list, rotate);
	}
	set_first(list);
}
