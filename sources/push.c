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

static void	operator(t_container **container, t_type src, t_type dest)
{
	t_stack	*tmp;

	if (!container[src]->head)
		return ;
	tmp = container[src]->head;
	container[src]->head = tmp->next;
	if (container[src]->head)
		container[src]->head->prev = NULL;
	else
		container[src]->tail = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	if (!container[dest]->head)
	{
		container[dest]->head = tmp;
		container[dest]->tail = tmp;
	}
	else
	{
		tmp->next = container[dest]->head;
		container[dest]->head->prev = tmp;
		container[dest]->head = tmp;
	}
	++container[dest]->size;
	--container[src]->size;
}

void	push(t_container **container, t_type type, bool print)
{
	if (type == A)
	{
		operator(container, B, A);
		if (print)
			ft_putendl_fd("pa", 1);
	}
	else if (type == B)
	{
		operator(container, A, B);
		if (print)
			ft_putendl_fd("pb", 1);
	}
}
