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

#include "pushswap.h"

char	*get_next_line(int fd);

typedef struct s_instruction
{
	void		((*f)(t_list **, t_type, bool));
	t_type		type;
	char		*code;
}				t_instruction;

static int	do_instruction(char *line, t_list **list)
{
	int							i;
	static const t_instruction	instruction[] = {
	{&swap, A, "sa\n"},
	{&swap, B, "sb\n"},
	{&swap, BOTH, "ss\n"},
	{&push, A, "pa\n"},
	{&push, B, "pb\n"},
	{&rotate, A, "ra\n"},
	{&rotate, B, "rb\n"},
	{&rotate, BOTH, "rr\n"},
	{&reverse_rotate, A, "rra\n"},
	{&reverse_rotate, B, "rrb\n"},
	{&reverse_rotate, BOTH, "rrr\n"}};

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

void	checker(t_list **list)
{
	char	*line;

	line = get_next_line(0);
	if (!line)
		return ;
	while (line)
	{
		if (do_instruction(line, list) == 0)
		{
			while (line)
			{
				free(line);
				line = get_next_line(0);
			}
			ft_putendl_fd("KO", 1);
			return ;
		}
		free(line);
		line = get_next_line(0);
	}
	if (is_sorted(list))
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
}
