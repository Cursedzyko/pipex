/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:36:53 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/19 15:23:18 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char    *get_cmd(char **paths, char *cmd)
{
    char    *tmp;
    char    *command;
    
    while(*paths)
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

void    free_cmd(t_data *data)
{
    int i;

    i = 0;
    while(data->args_cmd[i])
    {
        free(data->args_cmd[i]);
        i++;
    }
    free(data->args_cmd);
    free(data->cmd);
}