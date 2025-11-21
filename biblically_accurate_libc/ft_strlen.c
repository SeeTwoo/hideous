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

#include <stddef.h>
#include <stdint.h>
#include "bigass_string.h"

size_t	ft_strlen(char const *s)
{
	char const		*p;
	uintptr_t const	*word_ptr;
	uintptr_t		word;

	p = s;
	while ((uintptr_t)p & (sizeof(uintptr_t) - 1))
	{
		if (!(*p))
			return (p - s);
		p++;
	}
	word_ptr = (const uintptr_t *)p;
	while (1)
	{
		word = *word_ptr;
		if ((word - 0x0101010101010101) & ~word & 0x8080808080808080)
			break ;
		word_ptr++;
	}
	p = (char const *)word_ptr;
	while (*p)
		p++;
	return (p - s);
}

/*size_t	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/

#include <stdio.h>
int	main(void)
{
	int	i = 10000;
	size_t	len;
	
	while (i--)
		len = ft_strlen(BIGASS_STRING);
	printf("size is %lu\n", len);
	return (0);
}
