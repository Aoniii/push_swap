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

void	push(t_list **list, t_type type)
{
	if (type == A)
	{
		operator(list, B, A);
		ft_putendl_fd("pa", 1);
	}
	else if (type == B)
	{
		operator(list, A, B);
		ft_putendl_fd("pb", 1);
	}
}
