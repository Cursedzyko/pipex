/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:50:49 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/22 13:33:56 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	close_pipes(t_data *p)
{
	close(p->pipes[0]);
	close(p->pipes[1]);
}

void	child_in(t_data data, char **argv, char **envp)
{
	if ((dup2(data.pipes[1], STDOUT_FILENO)) < 0)
		ft_error_f("Error dup2", "child_in, pipes[1]", 2);
	if ((dup2(data.infile, STDIN_FILENO)) < 0)
		ft_error_f("Error dup2", "child_in, infile", 2);
	close_pipes(&data);
	close(data.infile);
	parse_args(&data, argv[2]);
	if (ft_strchr(data.args_cmd[0], '/') != 0)
	{
		if (access(data.args_cmd[0], F_OK) == 0)
			data.cmd = data.args_cmd[0];
		else
			ft_error_f(data.args_cmd[0], "No such file or directory", CMD_NOT_FOUND);
	}
	if (ft_strchr(data.args_cmd[0], '/') == 0)
		data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		ft_error_f("command not found", data.args_cmd[0], CMD_NOT_FOUND);
		free_cmd(&data);
		free_paths(&data);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
	{
		free_cmd(&data);
		free_paths(&data);
		ft_error_f("execve", "first error", -1);
	}
}

void	child_out(t_data data, char **argv, char **envp)
{
	if ((dup2(data.pipes[0], STDIN_FILENO)) < 0)
		ft_error_f("Error dup2", "child_out, pipes[0]", 2);
	if ((dup2(data.outfile, STDOUT_FILENO)) < 0)
		ft_error_f("Error dup2", "child_out, outfile", 2);
	close_pipes(&data);
	close(data.outfile);
	parse_args(&data, argv[3]);
	if (ft_strchr(data.args_cmd[0], '/') != 0)
	{
		if (access(data.args_cmd[0], F_OK) == 0)
			data.cmd = data.args_cmd[0];
		else
			ft_error_f(data.args_cmd[0], "No such file or directory", CMD_NOT_FOUND);
	}
	if (ft_strchr(data.args_cmd[0], '/') == 0)
		data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		ft_error_f("command not found", data.args_cmd[0], CMD_NOT_FOUND);
		free_cmd(&data);
		free_paths(&data);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
	{
		free_cmd(&data);
		free_paths(&data);
		ft_error_f("execve", "second error", -1);
	}
}
