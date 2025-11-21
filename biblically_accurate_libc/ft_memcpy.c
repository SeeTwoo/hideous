/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:07:46 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/25 13:36:45 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t		i;
	size_t		j;

	i = 0;
	while ((uintptr_t)(dest + i) & (sizeof(uintptr_t) - 1))
	{
		if (i == n)
			return (dest);
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	j = i + sizeof(uintptr_t);
	while (j < n)
	{
		((uintptr_t *)dest)[i] = ((uintptr_t *)src)[i];
		i = j;
		j += sizeof(uintptr_t);
	}
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
/*
void	*ft_memcpy(void *dest, void *src, size_t n) {
	for (size_t i = 0; i < n; i++)
		((char *)dest)[i] = ((char *)src)[i];
	return (dest);
}
*/

void	memswap(void *a, void *b) {
	char	c[128];

	memcpy(c, a, 128);
	memcpy(a, b, 128);
	memcpy(b, c, 128);
}

int	main(void)
{
	char	a[128];
	char	b[128];
	int		i = 100000000;

	memset(a, 'a', 128);
	memset(b, 'b', 128);
	while (i--)
		memswap(a, b);
	write(1, a, 128);
	write(1, b, 128);
	return (0);
}
