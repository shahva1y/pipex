/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krulindi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:54:36 by krulindi          #+#    #+#             */
/*   Updated: 2022/01/14 16:54:40 by krulindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_process_cmd1(int *fd, char **argv, char **envp)
{
	int		fd_infile;
	char	**command;
	char	**dirs;

	if (close(fd[0]) == -1)
		ft_error("Ошибка закрытия файлого декскпритора");
	fd_infile = open(argv[1], O_RDONLY, 0777);
	if (fd_infile == -1)
		ft_error("Ошибка открытия файла в дочернем процессе!");
	if (dup2(fd_infile, 0) == -1)
		ft_error("Ошибка создании копии файлого декскпритора");
	if (dup2(fd[1], 1) == -1)
		ft_error("Ошибка создании копии файлого декскпритора");
	command = ft_split(argv[2], ' ');
	if (!command)
		ft_error("Ошибка выделения памяти!");
	dirs = ft_get_path(envp);
	if (!dirs)
		ft_error("Ошибка выделения памяти!");
	if (execve(ft_get_command_path(command[0], dirs), command, envp) == -1)
		ft_error("Не получилось запустить команду дочернего процесса\n"
			"command not found");
}

static void	ft_process_cmd2(int *fd, char **argv, char **envp)
{
	int		fd_outfile;
	char	**command;
	char	**dirs;

	if (close(fd[1]) == -1)
		ft_error("Ошибка закрытия файлого декскпритора");
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_outfile == -1)
		ft_error("Ошибка открытия файла в родительском процессе!");
	if (dup2(fd[0], 0) == -1)
		ft_error("Ошибка открытия файла в дочернем процессе!");
	if (dup2(fd_outfile, 1) == -1)
		ft_error("Ошибка открытия файла в дочернем процессе!");
	command = ft_split(argv[3], ' ');
	if (!command)
		ft_error("Ошибка выделения памяти!");
	dirs = ft_get_path(envp);
	if (!dirs)
		ft_error("Ошибка выделения памяти!");
	if (execve(ft_get_command_path(command[0], dirs), command, envp) == -1)
		ft_error("Не получилось запустить команду родительского процесса!\n"
			"command not found");
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error("Не получилось создать канал чтениe/запись!");
		pid = fork();
		if (pid == -1)
			ft_error("Не получилось клонировать процесс!");
		if (!pid)
			ft_process_cmd1(fd, argv, envp);
		pid = fork();
		if (pid == -1)
			ft_error("Не получилось клонировать процесс!");
		if (!pid)
			ft_process_cmd2(fd, argv, envp);
		if (close(fd[1]) == -1 || close(fd[0]) == -1)
			ft_error("Ошибка закрытия файлого декскпритора [pipe]");
		if (wait(NULL) == -1 || wait(NULL) == -1)
			ft_error("Ошибка запуска функции wait()");
	}
	else
		ft_error("Не верной набор команды!");
	return (0);
}
