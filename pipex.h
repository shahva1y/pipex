/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krulindi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:25:12 by krulindi          #+#    #+#             */
/*   Updated: 2022/01/14 17:25:23 by krulindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

void	ft_error(char *str);
char	**ft_get_path(char **envp);
char	*ft_get_command_path(char *command, char **envp);

#endif
