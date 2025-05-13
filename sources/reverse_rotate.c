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

static void	operator(t_container **container, t_type type)
{
	t_stack	*tmp;

	if (!container[type]->head || !container[type]->head->next)
		return ;
	tmp = container[type]->tail;
	container[type]->tail = tmp->prev;
	container[type]->tail->next = NULL;
	tmp->next = container[type]->head;
	container[type]->head->prev = tmp;
	tmp->prev = NULL;
	container[type]->head = tmp;
}

void	reverse_rotate(t_container **container, t_type type, bool print)
{
	if (type == A)
	{
		operator(container, A);
		if (print)
			ft_putendl_fd("rra", 1);
	}
	else if (type == B)
	{
		operator(container, B);
		if (print)
			ft_putendl_fd("rrb", 1);
	}
	else if (type == BOTH)
	{
		operator(container, A);
		operator(container, B);
		if (print)
			ft_putendl_fd("rrr", 1);
	}
}
