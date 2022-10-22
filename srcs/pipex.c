/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:16:18 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/22 17:17:45 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_error_f(char *f, char *s, int err_exit)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(f, 2);
	ft_putstr_fd("\n", 2);
	exit(err_exit);
}

void	free_paths(t_data *data)
{
	int	i;

	i = 0;
	while (data->path_cmd[i])
	{
		free(data->path_cmd[i]);
		i++;
	}
	free(data->path_cmd);
}

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

static void	ft_init(t_data *data, int argc, char **argv, char **envp)
{
	data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (data->outfile < 0)
	{
		if (!access(argv[argc - 1], F_OK))
			ft_error_f(argv[argc - 1], "Permission denied", 0);
		ft_error_f(argv[argc - 1], "no such file or directory", ERR_FILE);
	}
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
	{
		if (!access(argv[1], F_OK))
			ft_error_f(argv[1], "Permission denied", 0);
		ft_error_f(argv[1], "no such file or directory", ERR_FILE);
	}
	data->path = find_path(envp);
	data->path_cmd = ft_split(data->path, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		ft_error_f(".\\pipex infile cmd1 cmd2 outfile", "Usage", 2);
	ft_init(&data, argc, argv, envp);
	if (pipe(data.pipes) < 0)
		ft_error_f("pipe", "Invalid", 2);
	data.pid[0] = fork();
	if (data.pid[0] == 0)
		child_in(data, argv, envp);
	data.pid[1] = fork();
	if (data.pid[1] == 0)
		child_out(data, argv, envp);
	close_pipes(&data);
	close(data.pipes[0]);
	close(data.pipes[1]);
	waitpid(data.pid[0], NULL, 0);
	waitpid(data.pid[1], &data.exit_status, 0);
	free_paths(&data);
	return (WEXITSTATUS(data.exit_status));
}
