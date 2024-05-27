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

void	cleanup(t_list **list)
{
	if (list && list[0])
		ft_lstclear(&list[0], &free);
	free(list);
	list = NULL;
}

int	main(int argc, char **argv)
{
	t_list	**list;

	list = malloc(sizeof(t_list *) * 2);
	if (!list || argc == 1)
	{
		free(list);
		list = NULL;
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	list[0] = args(&argv[1]);
	if (!list[0])
	{
		cleanup(list);
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	list[1] = NULL;
	cleanup(list);
	return (0);
}
