/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:20:24 by jibot             #+#    #+#             */
/*   Updated: 2022/04/08 17:00:26 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_pipex{
	int	f_in;
	int f_out;
	int end[2];
	char **path_split;
	char **cmd1;
	char **cmd2;
	pid_t child_1;
	pid_t child_2;
}	t_pipex;

void	child_1(t_pipex pipex, char **envp)
{
	int i;
	char	*cmd;

	pipex.child_1 = fork();
	if (pipex.child_1 == 0)
	{
		i = 0;
		dup2(pipex.f_in, STDIN_FILENO);
		dup2(pipex.end[1], STDOUT_FILENO);
		while (pipex.path_split[i])
		{
			cmd = ft_strjoin(pipex.path_split[i], "/");
			cmd = ft_strjoin(cmd, pipex.cmd1[0]);
			execve(cmd, pipex.cmd2, envp);
			i++;
		}
	}
	else
		waitpid(pipex.child_1, NULL, 0);
}

void	child_2(t_pipex pipex, char **envp)
{
	int i;
	char	*cmd;

	pipex.child_2 = fork();
	if (pipex.child_2 == 0)
	{
		i = 0;
		dup2(pipex.end[0], STDIN_FILENO);
		dup2(pipex.f_out, STDOUT_FILENO);
		while (pipex.path_split[i])
		{
			cmd = ft_strjoin(pipex.path_split[i], "/");
			cmd = ft_strjoin(cmd, pipex.cmd2[0]);
			execve(cmd, pipex.cmd2, envp);
			i++;
		}
	}
	else
		waitpid(pipex.child_2, NULL, 0);
}

void	get_paths(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	pipex->path_split = ft_split(envp[i] + 5, ':');
}

int	err_handle(t_pipex *pipex, char **argv, int argc)
{
	pipex->f_in = open(argv[1], O_RDONLY);
	pipex->f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->f_in < 0 || pipex->f_out < 0)
	{
		write(1, "Error : Wrong file name", 23);
		return (1);
	}
	close(pipex->f_in);
	close(pipex->f_out);
	return (0);
}

int main (int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[argc - 2], ' ');
	get_paths(&pipex, envp);
	if (err_handle(&pipex, argv, argc))
		return (1);
	pipex.f_in = open(argv[1], O_RDONLY);
	pipex.f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	pipe(pipex.end);
	child_1(pipex, envp);
	close(pipex.end[1]);
	child_2(pipex, envp);
	close(pipex.end[0]);
	return (0);
}
