/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:52:31 by snourry           #+#    #+#             */
/*   Updated: 2024/05/26 21:52:31 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

static bool	duplicate(char **argv)
{
	int	index;

	while (*argv)
	{
		index = 1;
		while (argv[index])
		{
			if (ft_strncmp(*argv, argv[index], 12) == 0)
				return (0);
			index++;
		}
		argv++;
	}
	return (1);
}

static char	**single_arg(char **argv, bool *b)
{
	if (ft_strrchr(argv[0], ' ') != NULL && argv[1] == NULL)
	{
		*b = 1;
		return (ft_split(argv[0], ' '));
	}
	*b = 0;
	return (argv);
}

t_container	*args(char **argv)
{
	t_container	*container;
	bool		b;

	argv = single_arg(argv, &b);
	if (!argv)
		return (NULL);
	if (!duplicate(argv))
	{
		if (b)
			free_argv(argv);
		return (NULL);
	}
	container = creat(argv);
	if (b)
		free_argv(argv);
	return (container);
}
