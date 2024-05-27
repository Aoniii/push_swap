/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:27:24 by snourry           #+#    #+#             */
/*   Updated: 2024/05/26 21:27:24 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

typedef enum e_type
{
	A,
	B,
	BOTH
}	t_type;

t_list	*args(char **argv);
void	swap(t_list **list, t_type type);
void	push(t_list **list, t_type type);
void	rotate(t_list **list, t_type type);
void	reverse_rotate(t_list **list, t_type type);

#endif
