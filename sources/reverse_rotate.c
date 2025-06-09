/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:42:56 by snourry           #+#    #+#             */
/*   Updated: 2024/05/27 13:42:56 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
*	Return the penultimate element
*/
static t_list	*list_penultimate(t_list *lst)
{
	t_list	*out;

	while (lst)
	{
		if (!lst->next)
			return (out);
		out = lst;
		lst = lst->next;
	}
	return (0);
}

/*
*	Operator for the reverse rotate
*	Return the list
*/
static void	operator(t_list **list)
{
	t_list	*tmp;

	if (!(*list) || !(*list)->next)
		return ;
	tmp = list_penultimate(*list);
	tmp->next->next = *list;
	*list = tmp->next;
	tmp->next = NULL;
}

/*
*	Reverse rotate the stack
*	Return the list
*/
void	reverse_rotate(t_list **list, t_type type, bool print)
{
	if (type == A)
	{
		operator(&list[A]);
		if (print)
			ft_putendl_fd("rra", 1);
	}
	else if (type == B)
	{
		operator(&list[B]);
		if (print)
			ft_putendl_fd("rrb", 1);
	}
	else if (type == BOTH)
	{
		operator(&list[A]);
		operator(&list[B]);
		if (print)
			ft_putendl_fd("rrr", 1);
	}
}
