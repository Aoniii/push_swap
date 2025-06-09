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
*	Check if the string is a valid integer
*	Return 1 if the string is a valid integer, 0 otherwise
*
*	Valid integer only:
*	-2147483648 to 2147483647
*
*	Invalid integer:
*	01, -01, +1
*/
static bool	check(char *s)
{
	int	index;

	index = 0;
	if (!s || !s[0])
		return (0);
	if (s[0] == '-' && s[1] != 0)
		index++;
	if (s[index] == '0' && (index != 0 || s[index + 1] != 0))
		return (0);
	while (s[index])
	{
		if (!ft_isdigit(s[index]))
			return (0);
		index++;
	}
	if (s[0] == '-' && (index > 11 || \
		(index == 11 && ft_strncmp("-2147483648", s, 20) < 0)))
		return (0);
	if (s[0] != '-' && (index > 10 || \
		(index == 10 && ft_strncmp("2147483647", s, 20) < 0)))
		return (0);
	return (1);
}

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
*	Create and Return the list
*/
static t_list	*creat(char **argv)
{
	t_list	*list;
	int		*nb;

	list = NULL;
	while (*argv)
	{
		nb = malloc(sizeof(int));
		if (!nb || !check(*argv))
		{
			free(nb);
			nb = NULL;
			ft_lstclear(&list, &free);
			return (NULL);
		}
		*nb = ft_atoi(*argv);
		ft_lstadd_back(&list, ft_lstnew(nb));
		argv++;
	}
	return (list);
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
