/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krulindi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:44:24 by krulindi          #+#    #+#             */
/*   Updated: 2022/01/15 16:44:28 by krulindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_connect_files(int *fd_files, char **argv, int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", 8) && ft_strlen(argv[1]) == 8)
	{
		fd_files[0] = ft_here_doc(argv[2]);
		fd_files[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else
	{
		fd_files[0] = open(argv[1], O_RDONLY, 0777);
		fd_files[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (fd_files[0] == -1)
		ft_error("Ошибка чтения файла!");
	if (dup2(fd_files[0], 0) == -1)
		ft_error("Ошибка дублирования файлового дескриптора!");
	if (fd_files[1] == -1)
		ft_error("Ошибка открытия файла!");
	if (dup2(fd_files[1], 1) == -1)
		ft_error("Ошибка дублирования файлового дескриптора!");
}

void	ft_execute_command(char *argv, char **envp)
{
	char	**dirs;
	char	**command;

	dirs = (char **)ft_get_path(envp);
	command = (char **) ft_split(argv, ' ');
	if (execve(ft_get_command_path(command[0], dirs), command, envp) == -1)
		ft_error("Не получилось запустить команду процесса!\n"
			"command not found");
}

static void	ft_process_fork(int *fd_files, char *argv, char **envp)
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
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			ft_error("Ошибка дублирования файлового дескриптора!");
		ft_execute_command(argv, envp);
	}
	if (close(fd[1]) == -1)
		ft_error("Ошибка при закрытии файла!");
	if (dup2(fd[0], 0) == -1)
		ft_error("Ошибка дублирования файлового дескриптора!");
	if (close(fd_files[0]) == -1)
		ft_error("Ошибка при закрытия файла!");
	fd_files[0] = fd[0];
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		fd_files[2];
	pid_t	pid;

	if (argc < 5)
		ft_error("Некорректный ввод аргументов\n");
	ft_connect_files(fd_files, argv, argc);
	i = 2;
	if (!ft_strncmp(argv[1], "here_doc", 8) && ft_strlen(argv[1]) == 8)
		i++;
	while (i < argc - 2)
		ft_process_fork(fd_files, argv[i++], envp);
	pid = fork();
	if (pid == -1)
		ft_error("Не удалось создать копию процесса!");
	if (!pid)
		ft_execute_command(argv[argc - 2], envp);
	if (close(fd_files[0]) == -1)
		ft_error("Ошибка закрытия файлого декскпритора [pipe]");
	if (waitpid(pid, NULL, 0) == -1)
		ft_error("Ошибка запуска функции waitpid()");
	return (0);
}
