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

/*
*	Find the min value of the list
*	Return the min value
*/
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

/*
*	Find the max value of the list
*	Return the max value
*/
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

/*
*	Identify the bottom value of the list
*	Return the bottom value
*/
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

/*
*	Identify the top value of the list
*	Return the top value
*/
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

/*
*	Get the median value of the list
*	Return the median value
*/
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
