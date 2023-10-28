/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:03:39 by snourry           #+#    #+#             */
/*   Updated: 2022/05/03 22:03:39 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

void	ft_sort_three(t_stack **stack)
{
	if (stack[A]->integer > stack[A]->next->integer)
		ft_swap(stack, A);
	if (stack[A]->next->next->integer != ft_get_max(stack, A))
		ft_reverse_rotate(stack, A);
	if (stack[A]->integer > stack[A]->next->integer)
		ft_swap(stack, A);
}

static void	ft_sort_four(t_stack **stack)
{
	while (ft_firststack(stack[A])->integer != ft_get_min(stack, A))
		ft_rotate(stack, A);
	ft_push(stack, B);
	ft_sort_three(stack);
	ft_push(stack, A);
}

static void	ft_sort_five(t_stack **stack)
{
	ft_setindex(stack);
	while (ft_firststack(stack[A])->index > 2)
		ft_rotate(stack, A);
	ft_push(stack, B);
	ft_sort_four(stack);
	ft_push(stack, A);
	if (stack[A]->integer > stack[A]->next->integer)
		ft_swap(stack, A);
}

void	ft_sort(t_stack **stack)
{
	int	size;

	size = ft_sizestack(stack[A]);
	if (size == 2)
		ft_swap(stack, A);
	else if (size == 3)
		ft_sort_three(stack);
	else if (size == 4)
		ft_sort_four(stack);
	else if (size == 5)
		ft_sort_five(stack);
	else if (size > 5)
		ft_sort_big(stack);
}
