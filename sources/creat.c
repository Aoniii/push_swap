/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:26:19 by snourry           #+#    #+#             */
/*   Updated: 2025/05/13 12:26:19 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static bool	check(char *s)
{
	int	index;

	index = 0;
	if (!s || !s[0])
		return (0);
	if (s[0] == '-' && s[1] != 0)
		index++;
	if (s[index] == '0' && (index != 0 || s[index + 1] != 0))
		return (0);
	while (s[index])
	{
		if (!ft_isdigit(s[index]))
			return (0);
		index++;
	}
	if (s[0] == '-' && (index > 11 || \
		(index == 11 && ft_strncmp("-2147483648", s, 20) < 0)))
		return (0);
	if (s[0] != '-' && (index > 10 || \
		(index == 10 && ft_strncmp("2147483647", s, 20) < 0)))
		return (0);
	return (1);
}

static int	*parse_number(char *arg)
{
	int	*nb;

	if (!check(arg))
		return (NULL);
	nb = malloc(sizeof(int));
	if (!nb)
		return (NULL);
	*nb = ft_atoi(arg);
	return (nb);
}

static t_stack	*append_stack_node(t_stack **head, t_stack **tail, int *nb)
{
	t_stack	*node;

	node = stack_new(nb);
	if (!node)
		return (NULL);
	node->prev = *tail;
	if (*tail)
		(*tail)->next = node;
	else
		*head = node;
	*tail = node;
	return (node);
}

static t_container	*out(t_stack *head, t_stack *tail, int size)
{
	t_container	*container;

	container = malloc(sizeof(t_container));
	if (!container)
	{
		stack_clear(&head, free);
		return (NULL);
	}
	container->head = head;
	container->tail = tail;
	container->size = size;
	return (container);
}

t_container	*creat(char **argv)
{
	t_stack	*head;
	t_stack	*tail;
	int		*nb;
	int		size;

	head = NULL;
	tail = NULL;
	size = 0;
	while (*argv && ++size)
	{
		nb = parse_number(*argv);
		if (!nb)
		{
			stack_clear(&head, free);
			return (NULL);
		}
		if (!append_stack_node(&head, &tail, nb))
		{
			free(nb);
			stack_clear(&head, free);
			return (NULL);
		}
		argv++;
	}
	return (out(head, tail, size));
}
