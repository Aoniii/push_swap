/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:21:19 by snourry           #+#    #+#             */
/*   Updated: 2024/05/27 12:21:19 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
*	Operator for the push
*	Return the list
*/
static void	operator(t_list **list, t_type src, t_type dest)
{
	t_list	*tmp;

	if (!list[src])
		return ;
	tmp = list[src];
	list[src] = list[src]->next;
	tmp->next = list[dest];
	list[dest] = tmp;
}

/*
*	Push the first element of the source stack to the destination stack
*	Return the list
*/
void	push(t_list **list, t_type type, bool print)
{
	if (type == A)
	{
		operator(list, B, A);
		if (print)
			ft_putendl_fd("pa", 1);
	}
	else if (type == B)
	{
		operator(list, A, B);
		if (print)
			ft_putendl_fd("pb", 1);
	}
}
