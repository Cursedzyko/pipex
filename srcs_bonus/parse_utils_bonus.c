/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:09:00 by zyunusov          #+#    #+#             */
/*   Updated: 2022/10/21 16:18:41 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	change_spaces(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '\'')
		{
			i++;
			while ((args[i] != '\'') && (args[i] != '\0'))
			{
				if (args[i] == ' ')
					args[i] = 1;
				i++;
			}
		}
		i++;
	}
}

static void	put_spaces(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((args[i] == '\'') && (args[i] != '\0'))
		{
			i++;
			while ((args[i] != '\'') && (args[i] != '\0'))
			{
				if (args[i] == 1)
					args[i] = ' ';
				i++;
			}
		}
		i++;
	}
}

static char	*remove_quotes(char *args)
{
	int		i;
	int		str_len;
	char	*new_str;

	i = 0;
	str_len = 0;
	while (args[i])
	{
		if (args[i] != '\'')
			str_len++;
		i++;
	}
	new_str = ft_calloc((str_len + 1), sizeof(char));
	i = 0;
	while (*args)
	{
		if (*args != '\'')
		{
			new_str[i] = *args;
			i++;
		}
		args++;
	}
	return (new_str);
}

void	parse_args(t_data *data, char *args)
{
	int		x;
	int		y;
	char	*tmp;

	y = 0;
	change_spaces(args);
	data->args_cmd = ft_split(args, ' ');
	while (data->args_cmd[y])
	{
		put_spaces(data->args_cmd[y]);
		x = 0;
		while (data->args_cmd[y][x])
		{
			if (data->args_cmd[y][x] == '\'')
			{
				tmp = data->args_cmd[y];
				data->args_cmd[y] = remove_quotes(data->args_cmd[y]);
				free(tmp);
				break ;
			}
			x++;
		}
		y++;
	}
}
