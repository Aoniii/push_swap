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
# include <stdio.h>

int	main(int argc, char **argv)
{
	t_list	**list;

	if (argc == 1)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	list = malloc(sizeof(t_list *) * 2);
	if (!list)
		return (1);
	list[0] = args(&argv[1]);
	list[1] = NULL;
	return (0);
}
