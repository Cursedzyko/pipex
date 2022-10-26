/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:50:49 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/27 00:34:28 by zyunusov         ###   ########.fr       */
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
		perror("Error dup2: ");
	dup2(data.infile, STDIN_FILENO);
	close_pipes(&data);
	close(data.infile);
	parse_args(&data, argv[2]);
	check_for_path(&data, 0);
	if (!data.cmd)
	{
		if (!ft_strchr(data.args_cmd[0], '/'))
			ft_error_f("command not found", data.args_cmd[0], 0);
		free_cmd(&data);
		free_paths(&data);
		exit (CMD_NOT_FOUND);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
	{
		free_cmd(&data);
		free_paths(&data);
		perror("Error execve: ");
	}
}

void	child_out(t_data data, char **argv, char **envp)
{
	if ((dup2(data.pipes[0], STDIN_FILENO)) < 0)
		perror("Error dup2: ");
	dup2(data.outfile, STDOUT_FILENO);
	close_pipes(&data);
	close(data.outfile);
	parse_args(&data, argv[3]);
	check_for_path(&data, 1);
	if (!data.cmd)
	{
		if (!ft_strchr(data.args_cmd[0], '/'))
			ft_error_f("command not found", data.args_cmd[0], CMD_NOT_FOUND);
		free_cmd(&data);
		free_paths(&data);
		exit (CMD_NOT_FOUND);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
	{
		free_cmd(&data);
		free_paths(&data);
		perror("Error execve: ");
	}
}
