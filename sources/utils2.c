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

int	find_min(t_list *list, int min)
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

int	find_max(t_list *list, int max)
{
	int	out;

	out = -2147483648;
	while (list)
	{
		if (*((int *)(list->content)) > out && *((int *)(list->content)) < max)
			out = *((int *)(list->content));
		list = list->next;
	}
	return (out);
}

int	identify_bottom(t_list *list, int bottom)
{
	int	prev;
	int	i;

	prev = get_min_value(list);
	i = 1;
	while (i < bottom)
	{
		prev = find_min(list, prev);
		i++;
	}
	return (prev);
}

int	identify_top(t_list *list, int top)
{
	int	prev;
	int	i;

	prev = get_max_value(list);
	i = 1;
	while (i < top)
	{
		prev = find_max(list, prev);
		i++;
	}
	return (prev);
}

int	get_median(t_list **list)
{
	int	prev;
	int	size;
	int	i;

	size = ft_lstsize(list[A]);
	prev = get_min_value(list[A]);
	i = 1;
	while (i < size / 2)
	{
		prev = find_min(list[A], prev);
		i++;
	}
	return (prev);
}
