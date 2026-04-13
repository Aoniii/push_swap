/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:34:22 by snourry           #+#    #+#             */
/*   Updated: 2024/06/02 15:34:22 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
*	Initialize the rotate
*/
t_rotate	init_rotate(void)
{
	t_rotate	rotate;

	rotate.ra = 0;
	rotate.rb = 0;
	rotate.rra = 0;
	rotate.rrb = 0;
	return (rotate);
}

/*
*	Count the number of rotate
*/
int	count_rotate(t_rotate rotate)
{
	int	i;

	i = 0;
	while (rotate.ra > 0 && rotate.rb > 0)
	{
		rotate.ra--;
		rotate.rb--;
		i++;
	}
	while (rotate.rra > 0 && rotate.rrb > 0)
	{
		rotate.rra--;
		rotate.rrb--;
		i++;
	}
	return (i + rotate.ra + rotate.rb + rotate.rra + rotate.rrb);
}
