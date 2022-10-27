/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:58:33 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/27 12:27:43 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_infile_check(char **argv, t_data *data)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
	{
		if (access(argv[1], F_OK | R_OK))
			ft_error_f(strerror(errno), argv[1], 0);
	}
}

int	ft_outfile_check(char **argv, t_data *data)
{
	if (!access(argv[4], F_OK | W_OK))
		data->outfile = open(argv[4], O_WRONLY | O_TRUNC);
	else if (!access(argv[4], F_OK))
	{
		ft_error_f(strerror(errno), argv[4], 0);
		return (1);
	}
	else
		data->outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	return (0);
}
