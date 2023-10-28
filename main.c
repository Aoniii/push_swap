/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:37:37 by snourry           #+#    #+#             */
/*   Updated: 2022/05/05 22:35:26 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdio.h>

static void	ft_freeall(t_stack **stack)
{
	if (stack[A])
		ft_freestack(stack[A]);
	if (stack[B])
		ft_freestack(stack[B]);
	free(stack);
	stack = NULL;
}

int	main(int argc, char **argv)
{
	t_stack	**stack;

	if (argc == 1)
		return (0);
	stack = malloc(sizeof(t_stack *) * 2);
	stack[A] = ft_get_args(argc, &argv[1]);
	stack[B] = NULL;
	if (!stack[A] || !ft_check_maxint(stack[A]) || !ft_check_mult(stack[A]))
		return (ft_error(stack));
	if (ft_check_sort(stack[A]))
		return (ft_freeall(stack), 0);
	ft_sort(stack);
	ft_freeall(stack);
	return (0);
}
