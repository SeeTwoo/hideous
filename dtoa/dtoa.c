/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:09:04 by wbeschon          #+#    #+#             */
/*   Updated: 2025/01/28 22:53:33 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*dtoa(double n)
{
	int 	int_part;
	int		decimal_part;
	double	decimal_part_temp;
	char	*str_int;
	char	*str_dec;
	char	*point;
	char	*number_temp;
	char	*number;

	int_part = (int)n;
	decimal_part_temp = n - int_part;
	decimal_part = decimal_part_temp * 1000000;
	str_int = ft_itoa(int_part);
	str_dec = ft_itoa(decimal_part);
	point = ft_strdup(".");
	number_temp = ft_strjoin(str_int, point);
	number = ft_strjoin(number_temp, str_dec);
	free(str_int);
	free(str_dec);
	free(point);
	free(number_temp);
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
