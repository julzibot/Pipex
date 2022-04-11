/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:20:24 by jibot             #+#    #+#             */
/*   Updated: 2022/04/11 19:04:06 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	child_1(t_pipex pipex, char **envp)
{
	int		i;
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
			if (!access(cmd, X_OK))
				execve(cmd, pipex.cmd1, envp);
			i++;
		}
		write (2, "command does not exist !\n", 25);
		exit (1);
	}
	else
		waitpid(pipex.child_1, NULL, 0);
}

void	child_2(t_pipex pipex, char **envp)
{
	int		i;
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
			if (!access(cmd, X_OK))
				execve(cmd, pipex.cmd2, envp);
			i++;
		}
		write (2, "command does not exist !\n", 25);
		exit (1);
	}
	else
		waitpid(pipex.child_2, NULL, 0);
}

int	get_paths(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
	{
		if (!envp[++i])
		{
			write(1, "PATH not found\n", 15);
			return (0);
		}
	}
	pipex->path_split = ft_split(envp[i] + 5, ':');
	return (1);
}

int	err_handle(t_pipex *pipex, char **argv, int argc, char **envp)
{
	pipex->f_in = open(argv[1], O_RDONLY);
	pipex->f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->f_in < 0 || pipex->f_out < 0)
	{
		perror ("Error");
		return (1);
	}
	if (argc != 5)
	{
		write(1, "Error : bad args input\n", 23);
		return (2);
	}
	if (envp[0] == NULL)
	{
		write(1, "Error : no environment\n", 23);
		return (3);
	}
	close(pipex->f_in);
	close(pipex->f_out);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[argc - 2], ' ');
	if (err_handle(&pipex, argv, argc, envp))
		return (1);
	if (!get_paths(&pipex, envp))
		return (2);
	pipex.f_in = open(argv[1], O_RDONLY);
	pipex.f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	pipe(pipex.end);
	child_1(pipex, envp);
	close(pipex.end[1]);
	child_2(pipex, envp);
	close(pipex.end[0]);
	return (0);
}
