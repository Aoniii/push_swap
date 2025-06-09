/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:38:35 by snourry           #+#    #+#             */
/*   Updated: 2024/06/04 22:38:35 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_bonus.h"

/*
*	Do the instruction
*	Return 1 if the instruction is valid, 0 otherwise
*/
static int	do_instruction(char *line, t_list **list)
{
	int							i;
	static const t_instruction	instruction[] = {
	{&swap, A, "sa"},
	{&swap, B, "sb"},
	{&swap, BOTH, "ss"},
	{&push, A, "pa"},
	{&push, B, "pb"},
	{&rotate, A, "ra"},
	{&rotate, B, "rb"},
	{&rotate, BOTH, "rr"},
	{&reverse_rotate, A, "rra"},
	{&reverse_rotate, B, "rrb"},
	{&reverse_rotate, BOTH, "rrr"}};

	i = 0;
	while (i < 11)
	{
		if (ft_strncmp(line, instruction[i].code, 5) == 0)
		{
			instruction[i].f(list, instruction[i].type, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
*	This is only if user double Ctrl+D for leave the terminal
*	for Free the line
*
*	Return:
*	1 if the instruction is valid,
*	2 if the instruction is not valid, (Error)
*	0 otherwise
*/
static int	double_ctrl_d(t_list **list, char *line)
{
	if (line && *line)
		if (do_instruction(line, list) == 0)
			return (2);
	return (1);
}

/*
*	Necessary for the Norminette
*	Loop for read the instruction
*
*	Return:
*	1 if the instruction is valid,
*	2 if the instruction is not valid, (Error)
*	0 otherwise
*/
static int	loop(t_list **list, char **line, char **tmp, int *res)
{
	char	buffer[2];

	*res = read(0, buffer, 1);
	buffer[*res] = '\0';
	if (*res == 0)
		return (double_ctrl_d(list, *line));
	else if (buffer[0] != '\n')
	{
		*tmp = ft_strjoin(*line, buffer);
		if (*line)
			free(*line);
		*line = *tmp;
	}
	else
	{
		if (do_instruction(*line, list) == 0)
		{
			free(*line);
			*line = NULL;
			return (2);
		}
		free(*line);
		*line = NULL;
	}
	return (0);
}

/*
*	Main function for the checker
*/
void	checker(t_list **list)
{
	char	*line;
	char	*tmp;
	int		res;
	int		ret;

	res = 1;
	line = NULL;
	while (res > 0)
	{
		ret = loop(list, &line, &tmp, &res);
		if (ret == 2)
			ft_putendl_fd("Error", 2);
		if (ret > 0)
			break ;
	}
	if (line)
		free(line);
	line = NULL;
	if (is_sorted(list) && ret != 2)
		ft_putendl_fd("OK", 1);
	else if (ret != 2)
		ft_putendl_fd("KO", 1);
}
