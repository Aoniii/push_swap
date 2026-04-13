/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:52:31 by snourry           #+#    #+#             */
/*   Updated: 2026/04/13 13:36:16 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
*	Check if the string is a valid integer
*	Return 1 if the string is a valid integer, 0 otherwise
*
*	Valid integer only:
*	-2147483648 to 2147483647
*
*	Invalid integer:
*	01, -01, +1
*/
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

/*
*	Create and Return the node
*/
t_list	*create_node(char *arg, t_list **list)
{
	int		*nb;
	t_list	*node;

	nb = malloc(sizeof(int));
	if (!nb || !check(arg))
	{
		free(nb);
		ft_lstclear(list, &free);
		return (NULL);
	}
	*nb = ft_atoi(arg);
	node = ft_lstnew(nb);
	if (!node)
	{
		free(nb);
		ft_lstclear(list, &free);
		return (NULL);
	}
	return (node);
}

/*
*	Create and Return the list
*/
t_list	*creat(char **argv)
{
	t_list	*list;
	t_list	*node;

	list = NULL;
	while (*argv)
	{
		node = create_node(*argv, &list);
		if (!node)
			return (NULL);
		ft_lstadd_back(&list, node);
		argv++;
	}
	return (list);
}
