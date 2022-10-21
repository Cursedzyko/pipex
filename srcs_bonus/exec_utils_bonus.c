/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:58:35 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/21 16:16:21 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	child_in(t_data data, char **argv, char **envp, int i)
{
	if ((dup2(data.pipes[i][1], STDOUT_FILENO)) < 0)
		ft_error_f("Error dup2", "child_in", 2);
	if ((dup2(data.infile, STDIN_FILENO)) < 0)
		ft_error_f("Error dup2", "child_in, infile", 2);
	close_pipes(&data);
	close(data.infile);
	parse_args(&data, argv[2 + data.have_here_doc]);
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		ft_error_f("command not found", data.args_cmd[0], CMD_NOT_FOUND);
		free_cmd(&data);
		free_paths(&data);
		free_pid_pipes(&data);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
	{
		free_cmd(&data);
		free_paths(&data);
		free_pid_pipes(&data);
		ft_error_f("execve", "first error", -1);
	}
}

void	child_mid(t_data data, char **argv, char **envp, int i)
{
	if ((dup2(data.pipes[i][1], STDOUT_FILENO)) < 0)
		ft_error_f("Error dup2", "child_mid", 2);
	if ((dup2(data.pipes[i - 1][0], STDIN_FILENO)) < 0)
		ft_error_f("Error dup2", "child_in, stdinpipe", 2);
	close_pipes(&data);
	parse_args(&data, argv[2 + i + data.have_here_doc]);
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		ft_error_f("command not found", data.args_cmd[0], CMD_NOT_FOUND);
		free_cmd(&data);
		free_paths(&data);
		free_pid_pipes(&data);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
	{
		free_cmd(&data);
		free_paths(&data);
		free_pid_pipes(&data);
		ft_error_f("execve", "first error", -1);
	}
}

void	child_out(t_data data, char **argv, char **envp, int i)
{
	if ((dup2(data.pipes[i - 1][0], STDIN_FILENO)) < 0)
		ft_error_f("Error dup2", "child_out, stdinpipe", 2);
	if ((dup2(data.outfile, STDOUT_FILENO)) < 0)
		ft_error_f("Error dup2", "child_out, outfile", 2);
	close_pipes(&data);
	close(data.outfile);
	parse_args(&data, argv[2 + i + data.have_here_doc]);
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		ft_error_f("command not found", data.args_cmd[0], CMD_NOT_FOUND);
		free_cmd(&data);
		free_paths(&data);
		free_pid_pipes(&data);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
	{
		free_cmd(&data);
		free_paths(&data);
		free_pid_pipes(&data);
		ft_error_f("execve", "first error", -1);
	}
}
