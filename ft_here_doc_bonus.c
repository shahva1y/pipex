/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krulindi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:24:38 by krulindi          #+#    #+#             */
/*   Updated: 2022/01/18 18:24:42 by krulindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static unsigned long long	ft_memmory_boost(char **line, int size)
{
	char				*newline;
	unsigned long long	length;
	unsigned long long	i;

	i = 0;
	length = ft_strlen(*line);
	newline = (char *) malloc((length + size) * sizeof(char));
	if (!newline)
		ft_error("Ошибка выделения памяти!");
	newline[length + size - 1] = '\0';
	while ((*line)[i])
	{
		newline[i] = (*line)[i];
		i++;
	}
	newline[i] = '\0';
	free((*line));
	(*line) = newline;
	return (length + size);
}

static unsigned long long	ft_get_next_line(int fd, char **buffer)
{
	unsigned long long	i;
	unsigned long long	size;
	char				c;

	size = 1000;
	(*buffer) = (char *)malloc(size * sizeof (char));
	if (!(*buffer))
		ft_error("Ошибка выделения памяти!");
	i = 0;
	while (read(fd, &c, 1) && c != '\n' && c != '\0')
	{
		(*buffer)[i] = c;
		if (i + 2 == size)
			size = ft_memmory_boost(buffer, 1000);
		i++;
	}
	if (c == '\n')
		(*buffer)[i] = '\n';
	if (c == '\n')
		i++;
	(*buffer)[i] = '\0';
	return (i);
}

static void	ft_console_input(int fd_infile, char *limiter)
{
	char	*line;

	write(1, "heredoc> ", 9);
	while (ft_get_next_line(0, &line))
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& ft_strlen(limiter) == ft_strlen(line) - 1)
		{
			free(line);
			exit(0);
		}
		write(fd_infile, line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 9);
	}
	exit(0);
}

int	ft_here_doc(char *limiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_error("Не удалось создать канал (pipe)!");
	pid = fork();
	if (pid == -1)
		ft_error("Не удалось создать копию процесса!");
	if (!pid)
	{
		if (close(fd[0]) == -1)
			ft_error("Ошибка при закрытии файла!");
		ft_console_input(fd[1], limiter);
	}
	if (dup2(fd[0], 0))
		ft_error("Ошибка дублирования файлового дескриптора!");
	if (close(fd[1]) == -1)
		ft_error("Ошибка при закрытии файла!");
	if (waitpid(pid, NULL, 0) == -1)
		ft_error("Ошибка запуска функции waitpid()");
	return (fd[0]);
}
