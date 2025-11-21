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
#include <string.h>

size_t	ft_strlen(char const *s)
{
	char const		*p;
	uintptr_t const	*word_ptr;

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
		if (((*word_ptr) - 0x0101010101010101) & ~(*word_ptr) & 0x8080808080808080)
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
	char	s[] = "hello";
	char	empty[] = "";
	char	longish[] = "  hello, this is a long string ya know";

	printf("len of [%s] is : %lu\n", s, ft_strlen(s));
	printf("len of [%s] is : %lu\n", empty, ft_strlen(empty));
	printf("len of [%s] is : %lu\n", longish, ft_strlen(longish));
	if (strlen(longish) != ft_strlen(longish))
		return (printf("fuuuuuuck\n"));
	return (0);
}
