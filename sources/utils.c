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

bool	is_sorted(t_container **container)
{
	t_stack	*tmp;

	tmp = container[A]->head;
	if (container[B]->head != NULL)
		return (false);
	while (tmp->next)
	{
		if (*((int *)(tmp->content)) > *((int *)(tmp->next->content)))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

int	get_max_value(t_stack *stack)
{
	int	out;

	out = *((int *)(stack->content));
	stack = stack->next;
	while (stack)
	{
		if (*((int *)(stack->content)) > out)
			out = *((int *)(stack->content));
		stack = stack->next;
	}
	return (out);
}

int	get_min_value(t_stack *stack)
{
	int	out;

	out = *((int *)(stack->content));
	stack = stack->next;
	while (stack)
	{
		if (*((int *)(stack->content)) < out)
			out = *((int *)(stack->content));
		stack = stack->next;
	}
	return (out);
}

int	get_at_index(t_stack *stack, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		stack = stack->next;
		i++;
	}
	return (*((int *)(stack->content)));
}
