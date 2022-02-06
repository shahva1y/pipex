/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krulindi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:44:51 by krulindi          #+#    #+#             */
/*   Updated: 2022/01/15 16:44:54 by krulindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

void				ft_error(char *str);
int					ft_here_doc(char *limiter);
char				**ft_get_path(char **envp);
char				*ft_get_command_path(char *command, char **dirs);

#endif