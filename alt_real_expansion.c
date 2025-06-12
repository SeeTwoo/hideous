/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_real_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seetwoo <waltibee@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:17:11 by seetwoo           #+#    #+#             */
/*   Updated: 2025/06/12 17:13:11 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	var_name_len(char *line, int i)
{
	size_t	len;

	i++;
	len = 0;
	while (line[i] && !ft_strchr(SEP, line[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	insert_string(t_minishell *sh, t_env_node *var, size_t len, int *k)
{
	size_t	new_size;
	size_t	line_end_len;
	char	*new_line;
	char	var_len;

	var_len = ft_strlen(var->value);
	new_size = ft_strlen(sh->line) + var_len - len;
	new_line = malloc(sizeof(char) * new_size);
	if (!new_line)
		return (1);
	ft_memcpy(new_line, sh->line, *k);
	ft_memcpy(&new_line[*k], var->value, var_len);
	line_end_len = ft_strlen(&sh->line[*k + len + 1]);
	ft_memcpy(&new_line[*k + var_len], &sh->line[*k + len], line_end_len);
	free(sh->line);
	sh->line = new_line;
//	printf("new_line is %s\n\n", new_line);
	return (0);
}

int	alt_real_expand_variable(t_minishell *sh, int *i)
{
	size_t		len;
	t_env_node	*var;

	len = var_name_len(sh->line, *i);
	var = sh->env_list->head;
	//printf("var to find is : %s, its len is %lu\n", &(sh->line)[*i + 1], len);
	while (var)
	{
		if (ft_strncmp(var->key, &(sh->line)[*i + 1], len + 1) == 0)
			break ;
		var = var->next;
	}
	if (!var)
	{
		(*i)++;
		return (0);
	}
//	printf("value is : %s\n", var->value);
	insert_string(sh, var, len, i);
	(*i)++;
	return (0);
}

int	alt_real_expansion(t_minishell *sh)
{
	int	exp_state;
	int	i;

	i = 0;
	exp_state = 1;
	while (sh->line[i])
	{
		if (exp_state && sh->line[i] == '\'')
			exp_state = 0;
		if (!exp_state && sh->line[i] == '\'')
			exp_state = 1;
		if (exp_state && sh->line[i] == '$')
			alt_real_expand_variable(sh, &i);
		else
			i++;
	}
	return (0);
}
