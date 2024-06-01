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

	i = 0;
	lst = list[A];
	while (*((int *)(lst->content)) != median)
	{
		lst = lst->next;
		i++;
	}
	if (i <= ft_lstsize(list[A]) - i)
		while (i--)
			rotate(list, A);
	else
	{
		i = ft_lstsize(list[A]) - i;
		while (i--)
			reverse_rotate(list, A);
	}
	push(list, B);
}

static void	push_b(t_list **list, int median)
{
	int	max;

	max = get_max_value(list[A]);
	while (list[A]->next)
	{
		if (*((int *)(list[A]->content)) != max)
		{
			push(list, B);
			if (*((int *)(list[B]->content)) > median)
			{
				if (*((int *)(list[A]->content)) == max && list[A]->next)
					rotate(list, BOTH);
				else
					rotate(list, B);
			}
		}
		else
			rotate(list, A);
	}
}

void	sort_big(t_list **list)
{
	int	median;

	median = get_median(list);
	push_median(list, median);
	push_b(list, median);
}
