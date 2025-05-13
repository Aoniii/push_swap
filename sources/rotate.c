/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rorate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:34:10 by snourry           #+#    #+#             */
/*   Updated: 2024/05/27 13:34:10 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	operator(t_container **container, t_type type)
{
	t_stack	*tmp;

	if (!container[type]->head || !container[type]->head->next)
		return ;
	tmp = container[type]->head;
	container[type]->head = tmp->next;
	container[type]->head->prev = NULL;
	container[type]->tail->next = tmp;
	tmp->prev = container[type]->tail;
	container[type]->tail = tmp;
	container[type]->tail->next = NULL;
}

void	rotate(t_container **container, t_type type, bool print)
{
	if (type == A)
	{
		operator(container, A);
		if (print)
			ft_putendl_fd("ra", 1);
	}
	else if (type == B)
	{
		operator(container, B);
		if (print)
			ft_putendl_fd("rb", 1);
	}
	else if (type == BOTH)
	{
		operator(container, A);
		operator(container, B);
		if (print)
			ft_putendl_fd("rr", 1);
	}
}
