/* ************************************************************************** */
/*                                                                            */
/*   microshell2.c                                         :::     ::::::::   */
/*                                                       :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*                                                   +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*                                                      #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int ft_cd(char **argv, int i)
{
    if (i  != 2)
        return (0);
    if (chdir(argv[i]) == -1)
    {
        write(2, "Error:cd\n", 10);
        return (0);
    }
    return (0);
}

void	ft_exec(char **argv, int i, char **env)
{
    int fd[2];
	int	pipe_after;
	int	pid;

    pipe_after = argv[i] && !strcmp(argv[i], "|");
    if (pipe_after && pipe(fd) == -1)
        return ;
    pid = fork();
    if (pid == 0)
    {
        argv[i] = 0;
        if (pipe_after && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
            return ;
        if (execve(*argv, argv, env))
        {
            write(2, "Error:exec\n", 12);
            return ;
        }
    }
    waitpid(pid, 0, 0);
    if (pipe_after && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
        return ;
    return ;
}

int main(int argc, char **argv, char **env)
{
    int i =0;

	(void)argc;
    while(argv[i] && argv[++i])
    {
        argv += i;
        i = 0;
        while(argv[i] && (strcmp(argv[i], "|") && strcmp(argv[i], ";")))
            i++;
        if (strcmp(*argv, "cd") == 0)
            ft_cd(argv, i);
        else if (i)
            ft_exec(argv, i, env);
    }
    return (0);
}
