/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krulindi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:55:52 by krulindi          #+#    #+#             */
/*   Updated: 2022/01/14 16:55:56 by krulindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

static void	ft_remove_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != (void *)0)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_get_path(char **envp)
{
	int		i;
	char	**dirs;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) && envp[i] != 0)
		i++;
	if (envp[i] == 0)
		ft_error("Не была найдена переменная окружения!");
	dirs = (char **) ft_split((envp[i] + 5), ':');
	if (!dirs)
		ft_error("Ошибка выделения памяти!");
	return (dirs);
}

char	*ft_get_command_path(char *command, char **dirs)
{
	char	*command_path;
	int		i;

	i = 0;
	if (!access(command, 0))
		return (command);
	command = ft_strjoin("/", command);
	if (!command)
		ft_error("Ошибка выделения памяти!");
	while (dirs[i] != 0)
	{
		command_path = ft_strjoin(dirs[i], command);
		if (!command_path)
			ft_error("Ошибка выделения памяти!");
		if (!access(command_path, 0))
			break ;
		free(command_path);
		i++;
	}
	if (dirs[i] == 0)
		ft_error("Введеной команды в системе не обнаружено!\ncommand not found");
	free(command);
	ft_remove_2d_array(dirs);
	return (command_path);
}
