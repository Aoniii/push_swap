/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:36:25 by snourry           #+#    #+#             */
/*   Updated: 2024/05/28 18:36:25 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		argv[i] = NULL;
		i++;
	}
	free(argv);
	argv = NULL;
}

bool	is_sorted(t_list **list)
{
	t_list	*tmp;

	tmp = list[A];
	if (list[B] != NULL)
		return (0);
	while (tmp->next)
	{
		if (*((int *)(tmp->content)) > *((int *)(tmp->next->content)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	get_max_value(t_list *list)
{
	int	out;

	out = *((int *)(list->content));
	list = list->next;
	while (list)
	{
		if (*((int *)(list->content)) > out)
			out = *((int *)(list->content));
		list = list->next;
	}
	return (out);
}

int	get_min_value(t_list *list)
{
	int	out;

	out = *((int *)(list->content));
	list = list->next;
	while (list)
	{
		if (*((int *)(list->content)) < out)
			out = *((int *)(list->content));
		list = list->next;
	}
	return (out);
}
