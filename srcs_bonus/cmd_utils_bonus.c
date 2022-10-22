/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:36:53 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/22 17:09:02 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		paths++;
		free(command);
	}
	return (NULL);
}

void	free_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->args_cmd[i])
	{
		free(data->args_cmd[i]);
		i++;
	}
	free(data->args_cmd);
	free(data->cmd);
}

void	check_for_path(t_data *data)
{
	if (ft_strchr(data->args_cmd[0], '/') != 0)
	{
		if (access(data->args_cmd[0], F_OK) == 0)
			data->cmd = data->args_cmd[0];
		else
			ft_error_f(data->args_cmd[0], "No such file or directory", 127);
	}
	if (ft_strchr(data->args_cmd[0], '/') == 0)
		data->cmd = get_cmd(data->path_cmd, data->args_cmd[0]);
}
