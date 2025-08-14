/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   microshell.c                                        :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <seetwoo@gmail.com>                 +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <stdio.h>

void	ft_cd(char **av, int i) {
	if (i != 2)
		return ;
	if (chdir(av[i]) == -1)
		write(2, "Error:cd\n", 9);
}

void	ft_exec(char **av, int i, char **envp) {
	int	fd[2];
	int	pid;
	int	pipe_after;

	pipe_after = av[i] && strcmp(av[i], "|") == 0;
	if (pipe_after && pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0) {
		av[i] = 0;
		if (pipe_after && (dup2(fd[1], 1) == -1 || close(fd[1]) == -1 || close(fd[0]) == -1))
			return ;
		if (execve(*av, av, envp)) {
			write(2, "Error:exec\n", 12);
			return ;
		}
	}
	waitpid(pid, 0, 0);
	if (pipe_after && (dup2(fd[1], 1) == -1 || close(fd[1]) == -1 || close(fd[0]) == -1))
		return ;
	return ;
}

int	main(int ac, char **av, char **envp) {
	int	i;

	(void)ac;
	i = 0;
	while (av[i] && av[++i]) {
		av += i;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (*av && strcmp(*av, "cd") == 0)
			ft_cd(av, i);
		else if (i)
			ft_exec(av, i, envp);
	}
	return (0);
}
