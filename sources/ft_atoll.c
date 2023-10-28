/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:24:46 by snourry           #+#    #+#             */
/*   Updated: 2022/05/03 22:52:24 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoll(char *nptr)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign *= -1;
	nptr--;
	while (*++nptr >= '0' && *nptr <= '9')
	{
		if (result == 0)
			result = *nptr - 48;
		else
			result = result * 10 + (*nptr - 48);
	}
	return (result * sign);
}
