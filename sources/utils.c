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

/*
*	Free the argv
*/
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

/*
*	Check if the list is sorted
*	Return 1 if the list is sorted, 0 otherwise
*/
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

/*
*	Get the max value of the list
*	Return the max value
*/
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

/*
*	Get the min value of the list
*	Return the min value
*/
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

/*
*	Get the value at the index
*	Return the value at the index
*/
int	get_at_index(t_list *list, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		list = list->next;
		i++;
	}
	return (*((int *)(list->content)));
}
