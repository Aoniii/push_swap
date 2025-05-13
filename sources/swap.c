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

static void	operator(t_container **container, t_type type)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	if (!container[type]->head || !container[type]->head->next)
		return ;
	tmp1 = container[type]->head;
	tmp2 = tmp1->next;
	if (tmp2->next)
		tmp2->next->prev = tmp1;
	tmp1->next = tmp2->next;
	tmp1->prev = tmp2;
	tmp2->next = tmp1;
	tmp2->prev = NULL;
	container[type]->head = tmp2;
	if (container[type]->size == 2)
		container[type]->tail = tmp1;
}

void	swap(t_container **container, t_type type, bool print)
{
	if (type == A)
	{
		operator(container, A);
		if (print)
			ft_putendl_fd("sa", 1);
	}
	else if (type == B)
	{
		operator(container, B);
		if (print)
			ft_putendl_fd("sb", 1);
	}
	else if (type == BOTH)
	{
		operator(container, A);
		operator(container, B);
		if (print)
			ft_putendl_fd("ss", 1);
	}
}
