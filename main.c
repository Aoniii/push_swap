/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:22:30 by snourry           #+#    #+#             */
/*   Updated: 2024/05/26 21:22:30 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	cleanup(t_container **container)
{
	if (container)
	{
		if (container[A])
			stack_clear(&container[A]->head, free);
		if (container[B])
			stack_clear(&container[B]->head, free);
		free(container[A]);
		free(container[B]);
		free(container);
	}
}

static bool	init_stack_b(t_container **container)
{
	container[B] = malloc(sizeof(t_container));
	if (!container[B])
		return (false);
	container[B]->head = NULL;
	container[B]->tail = NULL;
	container[B]->size = 0;
	return (true);
}

int	main(int argc, char **argv)
{
	t_container	**container;

	if (argc == 1)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	container = malloc(sizeof(t_container *) * 2);
	if (!container)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	container[A] = args(&argv[1]);
	if (!container[A] || !init_stack_b(container))
	{
		cleanup(container);
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	sort(container);
	cleanup(container);
	return (0);
}
