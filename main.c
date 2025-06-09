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

/*
*	Free the list and set it to NULL
*/
void	cleanup(t_list **list)
{
	if (list && list[A])
		ft_lstclear(&list[A], &free);
	free(list);
	list = NULL;
}

int	main(int argc, char **argv)
{
	t_list	**list;

	if (argc == 1)
		return (0);
	list = malloc(sizeof(t_list *) * 2);
	if (!list)
	{
		free(list);
		list = NULL;
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	list[A] = args(&argv[1]);
	if (!list[A])
	{
		cleanup(list);
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	list[B] = NULL;
	sort(list);
	cleanup(list);
	return (0);
}
