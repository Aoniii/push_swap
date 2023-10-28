/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:53:08 by snourry           #+#    #+#             */
/*   Updated: 2022/05/01 23:53:08 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

static void	ft_pa(t_stack **stack)
{
	t_stack	*src;
	t_stack	*dest;
	t_stack	*tmp;

	src = ft_firststack(stack[B]);
	dest = ft_firststack(stack[A]);
	if (!src)
		return ;
	tmp = src;
	if (src->next)
	{
		src = src->next;
		src->prev = NULL;
	}
	else
		src = NULL;
	stack[B] = src;
	tmp->next = dest;
	if (dest)
		dest->prev = tmp;
	stack[A] = tmp;
}

static void	ft_pb(t_stack **stack)
{
	t_stack	*src;
	t_stack	*dest;
	t_stack	*tmp;

	src = ft_firststack(stack[A]);
	dest = ft_firststack(stack[B]);
	if (!src)
		return ;
	tmp = src;
	if (src->next)
	{
		src = src->next;
		src->prev = NULL;
	}
	else
		src = NULL;
	stack[A] = src;
	tmp->next = dest;
	if (dest)
		dest->prev = tmp;
	stack[B] = tmp;
}

void	ft_push(t_stack **stack, enum e_stack type)
{
	if (type == A)
	{
		ft_pa(stack);
		ft_putendl_fd("pa", 1);
	}
	else if (type == B)
	{
		ft_pb(stack);
		ft_putendl_fd("pb", 1);
	}
}
