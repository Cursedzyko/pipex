/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:12:56 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/21 16:23:56 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"

# define CMD_NOT_FOUND 127
# define ERR_FILE 1

typedef struct s_data
{
	pid_t	*pid;
	int		infile;
	int		outfile;
	int		**pipes;
	int		exit_status;
	int		**here_doc;
	int		have_here_doc;
	int		total_cmds;
	char	*path;
	char	*cmd;
	char	**path_cmd;
	char	**args_cmd;
}	t_data;

void	ft_error_f(char *f, char *s, int err_exit);
void	free_paths(t_data *data);
char	*find_path(char **envp);
void	pipes_create(t_data *data, char **argv, char **envp);
void	ft_init_here_doc(t_data *data, int argc, char **argv, char **envp);
void	child_in(t_data data, char **argv, char **envp, int i);
void	child_mid(t_data data, char **argv, char **envp, int i);
void	child_out(t_data data, char **argv, char **envp, int i);
void	close_pipes(t_data *data);
char	*get_cmd(char **paths, char *cmd);
void	free_cmd(t_data *data);
void	free_pid_pipes(t_data *data);
void	parse_args(t_data *data, char *args);

#endif