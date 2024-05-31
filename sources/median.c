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

static int	get_min(t_list *list, int min)
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
	int		*tab;
	int		size;
	int		i;

	size = ft_lstsize(list[A]);
	tab = malloc(sizeof(int) * size);
	if (!tab)
		return (0);
	i = 1;
	tab[0] = get_min_value(list[A]);
	while (i < size)
	{
		tab[i] = get_min(list[A], tab[i - 1]);
		i++;
	}
	if (size % 2 == 0)
		i = (tab[size / 2 - 1] + tab[size / 2]) / 2;
	else
		i = tab[size / 2];
	free(tab);
	tab = NULL;
	return (i);
}
