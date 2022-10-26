/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:16:18 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/26 22:39:55 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_error_f(char *f, char *s, int err_exit)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(f, 2);
	ft_putstr_fd("\n", 2);
	if (err_exit == 1)
		exit(err_exit);
	if (err_exit == 127)
		exit(err_exit);
	if (err_exit == 3)
		err_exit++;
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

static int	ft_init(t_data *data, char **argv, char **envp)
{
	int status;

	status = 0;
	ft_infile_check(argv, data);
	status = ft_outfile_check(argv, data);
	data->path = find_path(envp);
	data->path_cmd = ft_split(data->path, ':');
	
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;
	

	if (argc != 5)
		ft_error_f(".\\pipex infile cmd1 cmd2 outfile", "Usage", 0);
	status = ft_init(&data, argv, envp);
	if (pipe(data.pipes) < 0)
		perror("Pipe error:");
	data.pid[0] = fork();
	if (data.pid[0] == 0)
		child_in(data, argv, envp);
	data.pid[1] = fork();
	if (data.pid[1] == 0)
		child_out(data, argv, envp);
	close_pipes(&data);
	close(data.infile);
	close(data.outfile);
	waitpid(data.pid[0], NULL, 0);
	waitpid(data.pid[1], &data.exit_status, 0);
	free_paths(&data);
	if (status == 1)
		return (1);
	return (WEXITSTATUS(data.exit_status));
}
