/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:29:31 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/17 11:33:21 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

# define CMD_NOT_FOUND 127
# define ERR_FILE 1

typedef struct s_data
{
	pid_t	pid[2];
	int		infile;
	int		outfile;
	int		pipes[2];
	int		exit_status;
	char	*path;
	char	*cmd;
	char	**path_cmd;
	char	**args_cmd;
}	t_data;

char	*get_cmd(char **paths, char *cmd);
void	free_cmd(t_data *p);
void	close_pipes(t_data *p);
void	ft_error_f(char *f, char *s, int err_exit);
void	free_paths(t_data *data);
void	child_in(t_data data, char **argv, char **envp);
void	child_out(t_data data, char **argv, char **envp);
void	parse_args(t_data *data, char *args);

#endif