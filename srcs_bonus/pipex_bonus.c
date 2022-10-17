/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:04:49 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/17 12:17:52 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_error_f(char *f, char *s, int err_exit)
{
	ft_putstr_fd(f, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	exit(err_exit);
}

static void	ft_init(t_data *data, int argc, char **argv, char **envp)
{
    data->have_here_doc = 0;
	data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (data->outfile < 0)
		ft_error_f("Invalid", "outfile", ERR_FILE);
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
	{
		if (!access(argv[1], F_OK))
			ft_error_f("Permission denied", "infile", 0);
		ft_error_f("Invalid", "infile", ERR_FILE);
	}
	data->path = find_path(envp);
	data->path_cmd = ft_split(data->path, ':');
    data->total_cmds = argc - 3;
    pipes_create(data, argv, envp);
    
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (argc < 5)
        ft_error_f("Usage", "./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", 2);
    else if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && (argc < 6))
        ft_error_f("Usage", "./pipex here_doc LIMITER cmd cmd1 file", 2);
    else if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && (argc >= 6))
        ft_init_here_doc(&data, argc, argv, envp);
    else if (argc >= 5)
        ft_init(&data, argc, argv, envp);
    return (WEXITSTATUS(data.exit_status));
}