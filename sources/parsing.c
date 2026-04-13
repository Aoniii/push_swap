/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:52:31 by snourry           #+#    #+#             */
/*   Updated: 2025/06/03 13:08:39 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

/*
*	Check if the list has duplicate values
*	Return 1 if the list has duplicate values, 0 otherwise
*/
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

/*
*	Check if the list has only one argument
*	Return 1 if the list has only one argument, 0 otherwise
*/
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

/*
*	Main function for the parsing
*	Return the list
*/
t_list	*args(char **argv)
{
	t_list	*list;
	bool	b;

	argv = single_arg(argv, &b);
	if (!argv)
		return (NULL);
	if (!duplicate(argv))
	{
		if (b)
			free_argv(argv);
		return (NULL);
	}
	list = creat(argv);
	if (b)
		free_argv(argv);
	return (list);
}
