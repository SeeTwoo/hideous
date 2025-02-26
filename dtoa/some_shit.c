/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:00:44 by wbeschon          #+#    #+#             */
/*   Updated: 2025/01/29 04:19:06 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <math.h>

int	fill_decimal_part(char *s, double decimal_part)
{
	int	i;
	int	temp_int;

	i = 0;
	while (i < 6)
	{
		decimal_part *= 10;
		temp_int = (int)round(decimal_part);
		decimal_part -= temp_int;
		s[i] = temp_int + '0';
		i++;
	}
	return (i);
}

char	*dtoa(double n)
{
	char	*number;
	char	*int_part;
	int		i;
	double	rounded_int;
	double	decimal_part;

	number = ft_calloc(50, sizeof(char));
	if (!number)
		return (NULL);
	i = 0;
	rounded_int = floor(n);
	int_part = ft_itoa((int)rounded_int);
	ft_strlcpy(number, int_part, 50);
	printf("number = %s\n\n", number);
	decimal_part = n - rounded_int;
	printf("decimal_part = %f\n\n", decimal_part);
	while (ft_isdigit(number[i]))
		i++;
	number[i] = '.';
	i++;
	fill_decimal_part(&number[i], decimal_part);
	return (number);
}

int	main(void)
{
	double	n = 2.252;
	char	*number;

	number = dtoa(n);
	printf("%s\n", number);
	free(number);
	return (0);
}
