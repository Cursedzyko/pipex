#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	pid_t	*pid;
	int		infile;
	int		outfile;
	int		**pipes;
	int		exit_status;
	
	int		have_here_doc;
	int		total_cmds;
	char	*path;
	char	*cmd;
	char	**path_cmd;
	char	**args_cmd;
} t_data;


#endif