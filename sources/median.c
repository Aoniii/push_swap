/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:31:41 by snourry           #+#    #+#             */
/*   Updated: 2024/05/31 11:31:41 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	find_min(t_list *list, int min)
{
	int	out;

	out = 2147483647;
	while (list)
	{
		if (*((int *)(list->content)) < out && *((int *)(list->content)) > min)
			out = *((int *)(list->content));
		list = list->next;
	}
	return (out);
}

int	get_median(t_list **list)
{
	int prev;
	int	size;
	int	i;

	size = ft_lstsize(list[A]);
	prev = get_min_value(list[A]);
	i = 1;
	while (i < size / 2 + 1)
	{
		prev = find_min(list[A], prev);
		i++;
	}
	return (prev);
}
