/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:05:58 by snourry           #+#    #+#             */
/*   Updated: 2024/05/27 12:05:58 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
*	Operator for the swap
*	Return the list
*/
static void	operator(t_list **list)
{
	t_list	*tmp;

	if (!(*list)->next)
		return ;
	tmp = *list;
	*list = (*list)->next;
	tmp->next = (*list)->next;
	(*list)->next = tmp;
}

/*
*	Swap the first two elements of the stack
*	Return the list
*/
void	swap(t_list **list, t_type type, bool print)
{
	if (type == A)
	{
		operator(&list[A]);
		if (print)
			ft_putendl_fd("sa", 1);
	}
	else if (type == B)
	{
		operator(&list[B]);
		if (print)
			ft_putendl_fd("sb", 1);
	}
	else if (type == BOTH)
	{
		operator(&list[A]);
		operator(&list[B]);
		if (print)
			ft_putendl_fd("ss", 1);
	}
}
