/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:20:24 by jibot             #+#    #+#             */
/*   Updated: 2022/02/08 20:28:01 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
/*void	child_process(int fd, char *cmd)
{
	dup2(f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
}*/

typedef struct	s_pipex{
	int	f_in;
	int f_out;
	int end_0;
	int end_1;
	char **path_split;
	char **cmd1;
	char **cmd2;
	pid_t child_1;
	pid_t child_2;
}	t_pipex;

void	child_1(t_pipex pipex, int argc, char **envp)
{
	dup2(pipex.f-in, STDIN_FILENO);
	dup2(pipex.end_1, STDOUT_FILENO);
	close(pipex.end_0);
	
}

void	child_2(t_pipex pipex, int argc, char **envp)
{

}

void	pipex(t_pipex pipex)
{
	int end[2];

	pipe(end);
	pipex.end_0 = end[0];
	pipex.end_1 = end[1];
	pipex.child_1 = fork();
	if (!pipex.child_1)
		child_1(pipex);
	pipex.child_2 = fork();
	if (!pipex.child_2)
		child_2(pipex);
}

int main (int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int i;
	char	**path_split;

	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[argc - 2], ' ');
	pipex.f_in = open(argv[1], O_RDONLY);
	if (pipex.f_in < 0)
		err_handle();
	pipex.f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex.f_out < 0)
		err_handle ();
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	pipex.path_split = ft_split(envp[i], ':');
	i = 0;
	pipex.child_1 = fork();
	if (pipex.child_1 == 0)
		child_1(pipex, argc, envp);
	pipex.child_2 = fork();
	if (pipex.child_2 == 0)
		child_2(pipex, argc, envp);
	return (0);
}
