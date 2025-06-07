/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:29:24 by snourry           #+#    #+#             */
/*   Updated: 2024/06/04 15:29:24 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_bonus.h"

void	cleanup(t_list **list)
{
	if (list && list[A])
		ft_lstclear(&list[A], &free);
	if (list && list[B])
		ft_lstclear(&list[B], &free);
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
	checker(list);
	cleanup(list);
	return (0);
}
