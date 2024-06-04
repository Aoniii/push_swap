/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:24:29 by snourry           #+#    #+#             */
/*   Updated: 2024/05/28 18:24:29 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	sort_three(t_list **list)
{
	if (*((int *)(list[A]->content)) > *((int *)(list[A]->next->content)))
		swap(list, A, 1);
	if (*((int *)(list[A]->next->next->content)) != get_max_value(list[A]))
		reverse_rotate(list, A, 1);
	if (*((int *)(list[A]->content)) > *((int *)(list[A]->next->content)))
		swap(list, A, 1);
}

static void	sort_four(t_list **list)
{
	while (*((int *)(list[A]->content)) != get_min_value(list[A]))
		rotate(list, A, 1);
	push(list, B, 1);
	sort_three(list);
	push(list, A, 1);
}

void	sort_five(t_list **list)
{
	int	min;

	min = identify_bottom(list[A], 2);
	while (*((int *)(list[A]->content)) > min)
		rotate(list, A, 1);
	push(list, B, 1);
	sort_four(list);
	push(list, A, 1);
	if (*((int *)(list[A]->content)) > *((int *)(list[A]->next->content)))
		swap(list, A, 1);
}

void	sort(t_list **list)
{
	int	size;

	if (is_sorted(list))
		return ;
	size = ft_lstsize(list[A]);
	if (size < 2)
		return ;
	else if (size == 2)
		swap(list, A, 1);
	else if (size == 3)
		sort_three(list);
	else if (size == 4)
		sort_four(list);
	else if (size == 5)
		sort_five(list);
	else
		sort_big(list);
}
